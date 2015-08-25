#include "Updateable.hpp"

Updateable::Updateable(bool enabled) {
	screenCollisions = new std::vector<Window>();
	objectCollisions = new std::vector<Updateable*>();

	this->enabled = enabled;
};

Updateable::~Updateable() {
	delete screenCollisions;
	delete objectCollisions;
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

sf::Vector2f Updateable::updatePosition(sf::Vector2f oldPosition, sf::Vector2f speed, sf::Clock clock) {
	float moveX = speed.x * clock.getElapsedTime().asSeconds();
	float moveY = speed.y * clock.getElapsedTime().asSeconds();

	this->oldPosition = oldPosition;
	newPosition = sf::Vector2f(oldPosition.x + moveX, oldPosition.y + moveY);
	return newPosition;
};

sf::Vector2f Updateable::checkCollisions(bool bounce, Updateable &object, std::vector<Updateable*>* objects) { 
	//NEED TO ADD COLLISION DETECTION
	return newPosition;
};

sf::Vector2f Updateable::updateCollisions(sf::RenderWindow* window, bool bounce, Updateable &object, std::vector<Updateable*>* objects) {
	//Reset Collision Values
	screenCollisions->clear();
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
