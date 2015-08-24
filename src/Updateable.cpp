#include "Updateable.hpp"

Updateable::Updateable() {
	screenCollision = new sf::Vector2u(0,0);
	objectCollisions = new std::vector<Updateable*>();
};

Updateable::~Updateable() {
	delete screenCollision;
	delete objectCollisions;
}

void Updateable::boundCheckScreen(sf::FloatRect bounds) {
	float positionX = newPosition.x;
	float positionY = newPosition.y;

	unsigned int screenHeight = window->getSize().y;
	unsigned int screenWidth = window->getSize().x;

	float shapeWidth = bounds.width;
	float shapeHeight = bounds.height;

	if (positionX < 0.f) {
		positionX = 0.f;
		screenCollision->x = 1;
	} else if (positionX + shapeWidth > screenWidth) {
		positionX = screenWidth - shapeWidth;
		screenCollision->x = 2;
	}
	if (positionY < 0.f) {
		positionY = 0.f;
		screenCollision->y = 1;
	} else if (positionY + shapeHeight > screenHeight) {
		positionY = screenHeight - shapeHeight;
		screenCollision->y = 2;
	}

	newPosition = sf::Vector2f(positionX, positionY);
};

sf::Vector2u Updateable::getScreenCollision() {
	return *screenCollision;
}

sf::Vector2f Updateable::updatePosition(sf::Vector2f oldPosition, sf::Vector2f speed, sf::Clock clock) {
	float moveX = speed.x * clock.getElapsedTime().asSeconds();
	float moveY = speed.y * clock.getElapsedTime().asSeconds();

	return (newPosition = sf::Vector2f(oldPosition.x + moveX, oldPosition.y + moveY));
};

sf::Vector2f Updateable::checkCollisions(unsigned int bounce, Updateable &object, std::vector<Updateable*>* objects) { 
	//NEED TO ADD COLLISION DETECTION
	return newPosition;
};

sf::Vector2f Updateable::updateCollisions(sf::RenderWindow* window, unsigned int bounce, Updateable &object, std::vector<Updateable*>* objects) {
	//Reset Collision Values
	screenCollision->x = 0;
	screenCollision->y = 0;
	objectCollisions->clear();

	//Set global window
	this->window = window;

	Updateable::boundCheckScreen(object.getBounds());
	Updateable::checkCollisions(bounce, object, objects);

	return newPosition;
}

std::vector<Updateable*>* Updateable::getObjectCollisions() {
	return objectCollisions;
}
