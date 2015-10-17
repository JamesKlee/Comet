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

	this->oldPosition = oldPosition;
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
				sf::FloatRect bounds = object.getShape()->getGlobalBounds();
				sf::FloatRect objectBounds = foundObject->getShape()->getGlobalBounds();

				if(bounds.intersects(objectBounds)) {
					objectCollisions->push_back(foundObject);

					switch(object.getShapeType()) {
					
						default:
							break;

						case circle:
							float width = object.getShape()->getGlobalBounds().width/2.f;
							sf::Vector2f origin =  newPosition + sf::Vector2f(width, width);

							switch (foundObject->getShapeType()) {

								default:
									break;

								case circle:
									float objectWidth = foundObject->getShape()->getGlobalBounds().width/2.f;
									sf::Vector2f objectOrigin = foundObject->getNewPosition() + sf::Vector2f(objectWidth, objectWidth);
									
									
									float distance = std::abs(sqrt( pow(objectOrigin.x - origin.x, 2.f) + pow(objectOrigin.y - origin.y, 2.f)));
									if (distance < bounds.width/2 + objectBounds.width/2) {
										sf::Vector2f originObject = object.getNewPosition() + sf::Vector2f(object.getShape()->getGlobalBounds().width/2, object.getShape()->getGlobalBounds().height/2);
										sf::Vector2f originFound = foundObject->getNewPosition() + sf::Vector2f(foundObject->getShape()->getGlobalBounds().width/2,foundObject->getShape()->getGlobalBounds().height/2);

										sf::Vector2f collision = originFound - originObject;
										sf::Vector2f tangent = sf::Vector2f(-collision.y, collision.x);
										newPosition = oldPosition;
										bounceObject(object, *foundObject, bounce, tangent);
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

void Updateable::bounceObject(Updateable &object, Updateable &foundObject, bool bounce, sf::Vector2f tangent) {

	if (!bounce) {
		return;
	}

	float theta = atan(tangent.x/tangent.y);

	float objectx = (object.getVelocity()->x) * cos(theta);
	float objecty = (object.getVelocity()->y) * cos(theta);
	float objectMass = M_PI * pow(object.getShape()->getGlobalBounds().width/2, 2.0);

	float foundx = (foundObject.getVelocity()->x) * cos(theta);
	float foundy = (foundObject.getVelocity()->y) * cos(theta);
	float foundMass = M_PI * pow(foundObject.getShape()->getGlobalBounds().width/2, 2.0);







};

sf::Vector2f* Updateable::getVelocity() {
	return velocity;
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

sf::Vector2f Updateable::getOldPosition() {
	return oldPosition;
}

bool Updateable::isSolid() {
	return solid;

}

ShapeEnum Updateable::getShapeType() {
	return shapeType;
}

void Updateable::setShapeType(ShapeEnum shapeType) {
	this->shapeType = shapeType;
}

