#ifndef PLAYER_H
#define PLAYER_H

#include "Updateable.hpp"
#include "GameObjects.hpp"
#include <vector>

class Player: public Updateable {
	public:
		Player();
		~Player();
		void update(sf::RenderWindow*, sf::Clock, std::vector<Updateable*>*);
		sf::FloatRect getBounds();

	private:
		
		sf::CircleShape* circle;
		float SPEED;
		float moveSpeedX;
		float moveSpeedY;
};

#endif
