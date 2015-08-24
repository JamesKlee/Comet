#ifndef PLAYER_H
#define PLAYER_H

#include "Updateable.hpp"

class Player: public Updateable {
	public:
		Player();
		~Player();
		void update(sf::RenderWindow*, sf::Clock);

	private:
		
		sf::CircleShape* circle;
		float SPEED;
		float moveSpeedX;
		float moveSpeedY;
};

#endif
