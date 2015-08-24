#include "GameLoop.hpp"

GameLoop::GameLoop() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::VideoMode resolution = sf::VideoMode::getDesktopMode();
    window = new sf::RenderWindow(resolution, "Comet", sf::Style::None, settings);
	window->setVerticalSyncEnabled(true);
	createStartingObjects();
};

GameLoop::~GameLoop() {
	delete window;
	delete gameObjects;
};

void GameLoop::createStartingObjects() {
	Updateable* player = new Player();

	gameObjects = new GameObjects();
	gameObjects->addObject(*player);
};

void GameLoop::start() {
	runGameLoop();
}

void GameLoop::runGameLoop() {
	sf::Clock clock;

    while (window->isOpen())
    {
	sf::Event event;
	while (window->pollEvent(event))
        {
            switch (event.type) {
		case sf::Event::Closed:
			window->close();
			break;
				
		case sf::Event::KeyPressed:
			switch(event.key.code) {
				case sf::Keyboard::Escape:
					window->close();
					break;							
						
				default:
					break;
			}
			break;

		default:
			break;

		}
	}

        window->clear();

	//Update all objects
	gameObjects->updateAll(window, clock);	
		
	clock.restart();
        window->display();
    }
};
