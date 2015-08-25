#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include "SFML/Graphics.hpp"
#include <vector>
#include "WindowEnum.hpp"

class GameObjects;

class Updateable {
	public:
		Updateable(bool);
		virtual ~Updateable();
		virtual void  update(sf::RenderWindow*, sf::Clock, std::vector<Updateable*>*) = 0; 
		bool getEnabled();
		void setEnabled(bool);
		sf::Vector2f getNewPosition();
		sf::Vector2f getOldPosition();

	protected:
		sf::Vector2f updatePosition(sf::Vector2f, sf::Vector2f, sf::Clock);
		sf::Vector2f updateCollisions(sf::RenderWindow*, bool, Updateable &, std::vector<Updateable*>*);
		std::vector<Window> getScreenCollisions();
		virtual sf::FloatRect getBounds() = 0;
		std::vector<Updateable*>* getObjectCollisions();
	
	private:
		void boundCheckScreen(sf::FloatRect);
		sf::Vector2f checkCollisions(bool, Updateable &, std::vector<Updateable*>*);

		sf::Vector2f newPosition;
		sf::Vector2f oldPosition;
		std::vector<Window>* screenCollisions;
		sf::RenderWindow* window;
		std::vector<Updateable*>* objectCollisions;
		bool enabled;
};

#endif
