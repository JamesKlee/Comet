#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "SFML/Graphics.hpp"
#include "GameObjects.hpp"
#include "Player.hpp"

class GameLoop {
	public:
		GameLoop();
		~GameLoop();
		void start();

	private:
		void runGameLoop();
		void createStartingObjects();

		sf::RenderWindow* window;
		GameObjects* gameObjects;
};

#endif
