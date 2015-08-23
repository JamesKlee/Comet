#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include "SFML/Graphics.hpp"

class Updateable {
	public:
		Updateable();
		virtual ~Updateable() {};
		virtual void  update(sf::RenderWindow*, sf::Clock) = 0; 
			
	protected:
		sf::Vector2f updatePosition(sf::Vector2f, sf::Vector2f, sf::Clock);
		sf::Vector2f checkCollisions(sf::RenderWindow*, sf::FloatRect);
		int getScreenCollision();

	private:
		void boundCheckScreen(sf::RenderWindow*,sf::FloatRect);
		
		sf::Vector2f newPosition;
		int screenCollision;
};

#endif
