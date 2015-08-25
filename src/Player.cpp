#include "Player.hpp"
#include <math.h>
#include <iostream>

Player::Player(bool enabled) : Player::Updateable(enabled) {
	SPEED = 1000.0f;

	circle = new sf::CircleShape(100.f, 10000);
	circle->setFillColor(sf::Color::Green);

	srand(time(NULL));
	moveSpeedX = rand()%((int)SPEED*2 + 1) - (int)SPEED;
	moveSpeedY = pow(pow(SPEED,2) - pow(moveSpeedX,2),0.5);
	
	if (rand()%(2) == 0) {
		moveSpeedY = -moveSpeedY;			
	}

};

Player::~Player() {
	delete circle;
};

void Player::update(sf::RenderWindow* window, sf::Clock clock, std::vector<Updateable*>* gameObjects) {

	if(!Player::getEnabled()) {
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		moveSpeedX = -SPEED;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		moveSpeedX = SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		moveSpeedY = -SPEED;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		moveSpeedY = SPEED;
	}

	sf::Vector2f velocity(moveSpeedX, moveSpeedY);
	Player::updatePosition(circle->getPosition(), velocity, clock);

	Player::updateCollisions(window, 0, *this, gameObjects);
	
	std::vector<Window> screenCollisions = Player::getScreenCollisions();
	
	sf::Vector2f position = getNewPosition();

	for (size_t i = 0; i < screenCollisions.size(); i++) {
		switch(screenCollisions.at(i)) {
			case WINDOW_TOP:
				position.y = 0.f;
				moveSpeedY = -moveSpeedY;
				break;

			case WINDOW_BOTTOM:
				position.y = window->getSize().y - getBounds().width;
				moveSpeedY = -moveSpeedY;
				break;

			case WINDOW_LEFT:
				position.x = 0.f;
				moveSpeedX = -moveSpeedX;
				break;

			case WINDOW_RIGHT:
				position.x = window->getSize().x - getBounds().width;
				moveSpeedX = -moveSpeedX;
				break;
		}
	}

	circle->setPosition(position);
	window->draw(*circle);	
};

sf::FloatRect Player::getBounds() {
	return circle->getGlobalBounds();	
};
