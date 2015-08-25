#include "GameObjects.hpp"

GameObjects::GameObjects() {
	objects = new std::vector<Updateable*>();
}

GameObjects::~GameObjects() {
	for (size_t i = 0; i < objects->size(); i++) {
		delete (objects->at(i));
	}
	delete objects;
}

int GameObjects::addObject(Updateable* object) {
	for (size_t i = 0; i < objects->size(); i++) {
		if (objects->at(i) == object) {
			return 0;
		}
	}
	objects->push_back(object);
	return 1;
};

int GameObjects::removeObject(Updateable* object) {
	for (size_t i = 0; i < objects->size(); i++) {
		if(objects->at(i) == object) {
			delete (objects->at(i));
			objects->erase(objects->begin() + i);
			return 1;
		}
	}
	return 0;
};

void GameObjects::updateAll(sf::RenderWindow* window, sf::Clock clock) {
	for (size_t i = 0; i < objects->size(); i ++) {
		(objects->at(i))->update(window, clock, objects);
	}
}
