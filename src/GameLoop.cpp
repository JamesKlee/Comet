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
	//DELETED in GameObjects destructor so automatically deleted
	//NEED TO BE CAREFUL IF OBJECTS ARE REMOVED AND NOT HANDLE
	gameObjects = new GameObjects();

	for (unsigned int i = 0; i < 10; i++) { 
		gameObjects->addObject(new Player(circle, true, true, sf::Vector2f(5.f, 5.f), new sf::Vector2f(350.f, 350.f)));
	}
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
