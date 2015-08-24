#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "SFML/Graphics.hpp"
#include <vector>
#include "Updateable.hpp"

class GameObjects {
	
	public:
		GameObjects();
		~GameObjects();
		int addObject(Updateable*);
		int removeObject(Updateable*);
		void updateAll(sf::RenderWindow*, sf::Clock);

	private:
		std::vector<Updateable*>* objects;
};

#endif
