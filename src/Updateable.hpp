#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include "SFML/Graphics.hpp"
#include <vector>
#include <math.h>
#include <cmath>
#include "WindowEnum.hpp"
#include "ShapeEnum.hpp"

#define _USE_MATH_DEFINES

class GameObjects;

class Updateable {
	public:
		Updateable(ShapeEnum, bool, bool, sf::Vector2f*);
		virtual ~Updateable();
		virtual void  update(sf::RenderWindow*, sf::Clock, std::vector<Updateable*>*) = 0; 
		bool getEnabled();
		void setEnabled(bool);
		sf::Vector2f getNewPosition();
		sf::Vector2f getOldPosition();

	protected:
		sf::Vector2f updatePosition(sf::Vector2f, sf::Clock);
		sf::Vector2f updateCollisions(sf::RenderWindow*, bool, Updateable &, std::vector<Updateable*>*);
		std::vector<Window> getScreenCollisions();
		virtual sf::Shape* getShape() = 0;
		bool isSolid();
		std::vector<Updateable*>* getObjectCollisions();
		ShapeEnum getShapeType();
		void setShapeType(ShapeEnum);
		sf::Vector2f* getVelocity();

	private:
		void boundCheckScreen(sf::FloatRect);
		sf::Vector2f checkCollisions(bool, Updateable &, std::vector<Updateable*>*);
		void bounceObject(Updateable &, Updateable &, bool, sf::Vector2f);

		sf::Vector2f newPosition;
		sf::Vector2f oldPosition;
		std::vector<Window>* screenCollisions;
		sf::RenderWindow* window;
		std::vector<Updateable*>* objectCollisions;
		bool enabled;
		bool solid;
		ShapeEnum shapeType;
		sf::Vector2f* velocity;
};

#endif
