#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f, 8);
    shape.setFillColor(sf::Color::Green);

	sf::RectangleShape rectangle(sf::Vector2f(120,50));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(sf::Vector2f(20,20));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
	window.draw(rectangle);
        window.display();
    }

    return 0;
}
