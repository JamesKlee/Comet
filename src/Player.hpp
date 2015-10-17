#ifndef PLAYER_H
#define PLAYER_H

#include "Updateable.hpp"
#include "GameObjects.hpp"

class Player: public Updateable {
	public:
		Player(ShapeEnum, bool, bool, sf::Vector2f, sf::Vector2f*);
		~Player();
		void update(sf::RenderWindow*, sf::Clock, std::vector<Updateable*>*);
		sf::Shape* getShape();
		ShapeEnum getShapeType();

	private:
		
		sf::CircleShape* circle;
		float moveSpeedX;
		float moveSpeedY;
};

#endif
