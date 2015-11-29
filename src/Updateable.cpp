#include "Updateable.hpp"
#include <iostream>

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

	if (newPosition.x < 0.f) {
		screenCollisions->push_back(WINDOW_LEFT);
	} else if (newPosition.x + shapeWidth > screenWidth) {
		screenCollisions->push_back(WINDOW_RIGHT);
	}
	if (newPosition.y < 0.f) {
		screenCollisions->push_back(WINDOW_TOP);
	} else if (newPosition.y + shapeHeight > screenHeight) {
		screenCollisions->push_back(WINDOW_BOTTOM);
	}
};

std::vector<Window> Updateable::getScreenCollisions() {
	return *screenCollisions;
}

sf::Vector2f Updateable::updatePosition(sf::Vector2f oldPosition, sf::Clock clock) {
		
	float moveX = velocity->x * clock.getElapsedTime().asSeconds();
	float moveY = velocity->y * clock.getElapsedTime().asSeconds();

	this->newPosition = sf::Vector2f( oldPosition.x + moveX, oldPosition.y + moveY);

	return newPosition;
};

sf::Vector2f Updateable::checkCollisions(bool bounce, Updateable &object, std::vector<Updateable*>* objects) { 
	//NEED TO ADD COLLISION DETECTION
	if (!solid) {
		return newPosition;
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
							sf::Vector2f objectOrigin =  newPosition + sf::Vector2f(objectWidth, objectWidth);

							switch (foundObject->getShapeType()) {

								default:
									break;

								case circle:
									float foundWidth = foundObject->getShape()->getGlobalBounds().width/2.f;
									sf::Vector2f foundOrigin = foundObject->getNewPosition() + sf::Vector2f(foundWidth, foundWidth);
									
									
									float distance = std::abs(sqrt( pow(foundOrigin.x - objectOrigin.x, 2.f) + pow(foundOrigin.y - objectOrigin.y, 2.f)));
									if (distance < objectBounds.width/2.f + foundBounds.width/2.f) {

										sf::Vector2f unitCV = sf::Vector2f(objectOrigin.x-foundOrigin.x, objectOrigin.y-foundOrigin.y)/distance;
										sf::Vector2f CV = unitCV * (objectBounds.width/2.f + foundBounds.width/2.f);
										newPosition = foundObject->getNewPosition() + CV;
										bounceObject(object, *foundObject, bounce);
									}
									break;

							} 
							break;
					}
				}
			}
		}
	}
	
	return newPosition;
};

void Updateable::bounceObject(Updateable &object, Updateable &foundObject, bool bounce) {

	if (!bounce) {
		return;
	}
	
	float sign = 0.f;

	float x1 = object.getNewPosition().x;
	float y1 = object.getNewPosition().y;
	float vx1 = object.getVelocity()->x;
	float vy1 = object.getVelocity()->y;
	float r1 = object.getShape()->getGlobalBounds().width/2.f;
	float m1 = M_PI * pow(r1,2.f);

	float x2 = foundObject.getNewPosition().x;
	float y2 = foundObject.getNewPosition().y;
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
	float R = 0.0; //CHANGE THIS LATER
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
	//Reset Collision Values
	screenCollisions->clear();
	objectCollisions->clear();

	//Set global window
	this->window = window;

	Updateable::boundCheckScreen(object.getShape()->getGlobalBounds());
	Updateable::checkCollisions(bounce, object, objects);

	return newPosition;
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

sf::Vector2f Updateable::getNewPosition() {
	return newPosition;
}

void Updateable::setPosition(sf::Vector2f newPos) {
	newPosition = newPos;
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

