#include "Player.hpp"
#include <math.h>

Player::Player() {
	SPEED = 1000.0f;

	circle = new sf::CircleShape(100.f, 10000);
	circle->setFillColor(sf::Color::Green);
};

Player::~Player() {
	delete circle;
};

void Player::update(sf::RenderWindow* window, sf::Clock clock) {
	
	srand(time(NULL));
	float moveSpeedX = rand()%((int)SPEED*2 + 1) - (int)SPEED;
	float moveSpeedY = pow(pow(SPEED,2) - pow(moveSpeedX,2),0.5);
	if (rand()%(2) == 0) {
		moveSpeedY = -moveSpeedY;			
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
	sf::Vector2f newPosition = Player::updatePosition(circle->getPosition(), velocity, clock);
	
	sf::Vector2f position = Player::boundCheckScreen(newPosition, window, circle->getGlobalBounds());
	circle->setPosition(position);

	window->draw(*circle);	
};
