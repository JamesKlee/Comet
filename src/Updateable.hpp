#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include "SFML/Graphics.hpp"
#include <vector>

class GameObjects;

class Updateable {
	public:
		Updateable();
		virtual ~Updateable();
		virtual void  update(sf::RenderWindow*, sf::Clock, std::vector<Updateable*>*) = 0; 

	protected:
		sf::Vector2f updatePosition(sf::Vector2f, sf::Vector2f, sf::Clock);
		sf::Vector2f updateCollisions(sf::RenderWindow*, unsigned int, Updateable &, std::vector<Updateable*>*);
		sf::Vector2u getScreenCollision();
		virtual sf::FloatRect getBounds() = 0;
		std::vector<Updateable*>* getObjectCollisions();

	private:
		void boundCheckScreen(sf::FloatRect);
		sf::Vector2f checkCollisions(unsigned int, Updateable &, std::vector<Updateable*>*);

		sf::Vector2f newPosition;
		sf::Vector2f oldPosition;
		sf::Vector2u* screenCollision;
		sf::RenderWindow* window;
		std::vector<Updateable*>* objectCollisions;
};

#endif
