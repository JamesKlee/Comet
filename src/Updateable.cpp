#include "Updateable.hpp"
#include <iostream>
#include <algorithm>

Updateable::Updateable(ShapeEnum shapeType, bool enabled, bool solid, sf::Vector2f* velocity) {
	screenCollisions = new std::vector<Window>();
	objectCollisions = new std::vector<Updateable*>();

	this->shapeType = shapeType;
	this->enabled = enabled;
	this->solid = solid;

	this->velocity = velocity;
};

Updateable::~Updateable() {
	delete screenCollisions;
	delete objectCollisions;
	delete velocity;
}

void Updateable::boundCheckScreen(sf::FloatRect bounds) {

	unsigned int screenHeight = window->getSize().y;
	unsigned int screenWidth = window->getSize().x;

	float shapeWidth = bounds.width;
	float shapeHeight = bounds.height;

	if ((position.x < 0.f) and (std::find(screenCollisions->begin(), screenCollisions->end(), WINDOW_LEFT) == screenCollisions->end())) {
		position.x = 0.f;
		screenCollisions->push_back(WINDOW_LEFT);
	} else if ((position.x + shapeWidth > screenWidth) and (std::find(screenCollisions->begin(), screenCollisions->end(), WINDOW_RIGHT) == screenCollisions->end())) {
		position.x = window->getSize().x - getShape()->getGlobalBounds().width;
		screenCollisions->push_back(WINDOW_RIGHT);
	}
	if ((position.y < 0.f) and (std::find(screenCollisions->begin(), screenCollisions->end(), WINDOW_TOP) == screenCollisions->end())) {
		position.y = 0.f;
		screenCollisions->push_back(WINDOW_TOP);
	} else if ((position.y + shapeHeight > screenHeight) and (std::find(screenCollisions->begin(), screenCollisions->end(), WINDOW_BOTTOM) == screenCollisions->end())) {
		position.y = window->getSize().y - getShape()->getGlobalBounds().height;
		screenCollisions->push_back(WINDOW_BOTTOM);
	}
};

std::vector<Window> Updateable::getScreenCollisions() {
	return *screenCollisions;
}

sf::Vector2f Updateable::updatePosition(sf::Vector2f oldPosition, sf::Clock clock) {

	//Reset Collision Values
	screenCollisions->clear();
	objectCollisions->clear();
		
	float moveX = velocity->x * clock.getElapsedTime().asSeconds();
	float moveY = velocity->y * clock.getElapsedTime().asSeconds();

	this->position = sf::Vector2f( oldPosition.x + moveX, oldPosition.y + moveY);

	return position;
};

sf::Vector2f Updateable::checkCollisions(bool bounce, Updateable &object, std::vector<Updateable*>* objects) { 
	//NEED TO ADD COLLISION DETECTION
	if (!solid) {
		return position;
	}

	
	for (size_t i = 0; i < objects->size(); i++) {
		if (objects->at(i) != &object) {
			Updateable* foundObject = objects->at(i);
						
			if (foundObject->getEnabled() && foundObject->isSolid()) {
				sf::FloatRect objectBounds = object.getShape()->getGlobalBounds();
				sf::FloatRect foundBounds = foundObject->getShape()->getGlobalBounds();

				if(objectBounds.intersects(foundBounds)) {
					objectCollisions->push_back(foundObject);

					switch(object.getShapeType()) {
					
						default:
							break;

						case circle:
							float objectWidth = object.getShape()->getGlobalBounds().width/2.f;
							sf::Vector2f objectOrigin =  position + sf::Vector2f(objectWidth, objectWidth);

							switch (foundObject->getShapeType()) {

								default:
									break;

								case circle:
									float foundWidth = foundObject->getShape()->getGlobalBounds().width/2.f;
									sf::Vector2f foundOrigin = foundObject->getPosition() + sf::Vector2f(foundWidth, foundWidth);
									
									
									float distance = std::abs(sqrt( pow(foundOrigin.x - objectOrigin.x, 2.f) + pow(foundOrigin.y - objectOrigin.y, 2.f)));
									if (distance < objectBounds.width/2.f + foundBounds.width/2.f) {

										sf::Vector2f unitCV = sf::Vector2f(foundOrigin.x-objectOrigin.x, foundOrigin.y-objectOrigin.y)/distance;
										if (unitCV.x == 0.f and unitCV.y == 0.f) {
											unitCV.x = 1.f;
											unitCV.y = 1.f;
										}
										sf::Vector2f CV = unitCV * (objectBounds.width/2.f + foundBounds.width/2.f);
										foundObject->setPosition(getPosition() + CV);
										//foundObject->checkCollisions(true, *foundObject, objects);
									//	bounceObject(object, *foundObject, bounce);
									}
									break;

							} 
							break;
					}
				}
			}
		}
	}
	
	return position;
};

void Updateable::bounceObject(Updateable &object, Updateable &foundObject, bool bounce) {

	if (!bounce) {
		return;
	}
	
	float sign = 0.f;

	float x1 = object.getPosition().x;
	float y1 = object.getPosition().y;
	float vx1 = object.getVelocity()->x;
	float vy1 = object.getVelocity()->y;
	float r1 = object.getShape()->getGlobalBounds().width/2.f;
	float m1 = M_PI * pow(r1,2.f);

	float x2 = foundObject.getPosition().x;
	float y2 = foundObject.getPosition().y;
	float vx2 = foundObject.getVelocity()->x;
	float vy2 = foundObject.getVelocity()->y;
	float r2 = foundObject.getShape()->getGlobalBounds().width/2.f;
	float m2 = M_PI * pow(r2,2.f);

	float x21 = x2 - x1;
	float y21 = y2 - y1;
	float vx21 = vx2 - vx1;
	float vy21 = vy2 - vy2;
	float m21 = m2/m1;

	float vx_cm = (m1*vx1 + m2*vx2) / (m1 + m2);
	float vy_cm = (m1*vy1 + m2*vy2) / (m1 + m2);

	//Return old velocities if not approaching
	if ( (vx21*x21 + vy21*y21) >= 0) {
		return;
	} 

	float fy21 = 1.0E-12*fabs(y21);                            
	if ( fabs(x21) < fy21 ) {  
		if (x21 < 0) { 
			sign = -1;
		} else { 
			sign = 1;
		}  
		x21 = fy21*sign; 
	} 

	//update velocities
	float a = y21/x21;
	float dvx2 = -2*(vx21 + a*vy21)/((1 + a*a)*(1 + m21));
	vx2 = vx2 + dvx2;
	vy2 = vy2 + a*dvx2;
	vx1 = vx1 - m21*dvx2;
	vy1 = vy1 - a*m21*dvx2;

	//velocity correction for inelastic collisions
	float R = 1.0; //CHANGE THIS LATER
	vx1 = (vx1-vx_cm)*R + vx_cm;
	vy1 = (vy1-vy_cm)*R + vy_cm;
	vx2 = (vx2-vx_cm)*R + vx_cm;
	vy2 = (vy2-vy_cm)*R + vy_cm;

	//Update velocities
	object.setVelocity(new sf::Vector2f(vx1,vy1));
	foundObject.setVelocity(new sf::Vector2f(vx2,vy2));
};

sf::Vector2f* Updateable::getVelocity() {
	return velocity;
};

void Updateable::setVelocity(sf::Vector2f* newVelocity) {
	velocity = newVelocity;
};

sf::Vector2f Updateable::updateCollisions(sf::RenderWindow* window, bool bounce, Updateable &object, std::vector<Updateable*>* objects) {
	//Set global window
	this->window = window;

	Updateable::boundCheckScreen(object.getShape()->getGlobalBounds());
	Updateable::checkCollisions(bounce, object, objects);

	return position;
}

std::vector<Updateable*>* Updateable::getObjectCollisions() {
	return objectCollisions;
}

bool Updateable::getEnabled() {
	return enabled;
}

void Updateable::setEnabled(bool enabled) {
	this->enabled = enabled;
}

sf::Vector2f Updateable::getPosition() {
	return position;
}

void Updateable::setPosition(sf::Vector2f newPos) {
	position = newPos;
};

bool Updateable::isSolid() {
	return solid;

}

ShapeEnum Updateable::getShapeType() {
	return shapeType;
}

void Updateable::setShapeType(ShapeEnum shapeType) {
	this->shapeType = shapeType;
}

