#include "Updateable.hpp"

sf::Vector2f Updateable::boundCheckScreen(sf::Vector2f position, sf::RenderWindow* window, sf::FloatRect bounds) {
	float positionX = position.x;
	float positionY = position.y;

	unsigned int screenHeight = window->getSize().y;
	unsigned int screenWidth = window->getSize().x;

	float shapeWidth = bounds.width;
	float shapeHeight = bounds.height;

	if (positionX < 0.f) {
		positionX = 0.f;	
	} else if (positionX + shapeWidth > screenWidth) {
		positionX = screenWidth - shapeWidth;
	}
	if (positionY < 0.f) {
		positionY = 0.f;
	} else if (positionY + shapeHeight > screenHeight) {
		positionY = screenHeight - shapeHeight;	
	}

	return sf::Vector2f(positionX, positionY);
};

sf::Vector2f Updateable::updatePosition(sf::Vector2f oldPosition, sf::Vector2f speed, sf::Clock clock) {
	float moveX = speed.x * clock.getElapsedTime().asSeconds();
	float moveY = speed.y * clock.getElapsedTime().asSeconds();

	return sf::Vector2f(oldPosition.x + moveX, oldPosition.y + moveY);
}
