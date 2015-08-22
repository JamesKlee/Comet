#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include "SFML/Graphics.hpp"


class Updateable {
	public:
		virtual ~Updateable() {};
		virtual void  update(sf::RenderWindow*, sf::Clock) = 0; 
		sf::Vector2f boundCheckScreen(sf::Vector2f, sf::RenderWindow*,sf::FloatRect);
		sf::Vector2f updatePosition(sf::Vector2f, sf::Vector2f, sf::Clock);
	
};

#endif
