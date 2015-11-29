#include "Player.hpp"
#include <math.h>
#include <iostream>

Player::Player(ShapeEnum shapeType, bool enabled, bool solid, sf::Vector2f pos, sf::Vector2f* velocity) : Player::Updateable(shapeType, enabled, solid, velocity) {

	circle = new sf::CircleShape(100.f);
	circle->setFillColor(sf::Color::Green);
	circle->setPosition(pos);
};

Player::~Player() {
	delete circle;
};

void Player::update(sf::RenderWindow* window, sf::Clock clock, std::vector<Updateable*>* gameObjects) {

	if(!Player::getEnabled()) {
		return;
	}

	float *speedX = &Updateable::getVelocity()->x;
	float *speedY = &Updateable::getVelocity()->y;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		*speedX = -std::abs(*speedX);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		*speedX = std::abs(*speedX);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		*speedY = -std::abs(*speedY);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		*speedY = std::abs(*speedY);
	}

	Player::updatePosition(circle->getPosition(), clock);

	std::vector<Window> screenCollisions = Player::getScreenCollisions();
	sf::Vector2f position = getNewPosition();

	for (size_t i = 0; i < screenCollisions.size(); i++) {
		switch(screenCollisions.at(i)) {
			case WINDOW_TOP:
				position.y = 0.f;
				*speedY = -(*speedY);
				break;

			case WINDOW_BOTTOM:
				position.y = window->getSize().y - getShape()->getGlobalBounds().height;
				*speedY = -(*speedY);
				break;

			case WINDOW_LEFT:
				position.x = 0.f;
				*speedX = -(*speedX);
				break;

			case WINDOW_RIGHT:
				position.x = window->getSize().x - getShape()->getGlobalBounds().width;
				*speedX = -*(speedX);
				break;
		}
	}
	setPosition(position);

	Player::updateCollisions(window, true, *this, gameObjects);
	position = getNewPosition();

	circle->setPosition(position);
	window->draw(*circle);	
};

sf::Shape* Player::getShape() {
	return circle;
};
