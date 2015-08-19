#include <SFML/Graphics.hpp>

int main()
{
   	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	sf::CircleShape shape(100.f, 8);
    	shape.setFillColor(sf::Color::Green);

	sf::View view(sf::FloatRect(0, 0, window.getSize().x/4, window.getSize().y/4));
	view.setViewport(sf::FloatRect(0, 0, 1, 1));
	window.setView(view);

	float cameraSpeed = 25.0f;
	
	sf::Clock clock;
    	while (window.isOpen())
    	{
        	sf::Event event;
        	while (window.pollEvent(event))
        	{
        	    
			switch (event.type) {
				case (sf::Event::Closed):
        	        		window.close();
					break;

				case (sf::Event::KeyPressed):
					
					switch(event.key.code) {
						case (sf::Keyboard::Escape):
							window.close();
							break;
						
						default:
							break;
					}						
					break;				

				default:
					break;
			}
        	}
		
		
		float moveViewX = 0.0f;
		float moveViewY = 0.0f;	

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			moveViewX = -cameraSpeed;		
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { 
			moveViewX = cameraSpeed;
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { 
			moveViewY = -cameraSpeed;
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { 
			moveViewY = cameraSpeed;
		}

        	window.clear();

		sf::Time elapsedTime = clock.restart();
		view.move(moveViewX * elapsedTime.asSeconds(), moveViewY * elapsedTime.asSeconds());
		window.setView(view);
        	window.draw(shape);
        	window.display();
    	}

    return 0;
}
