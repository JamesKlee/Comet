#include "GameLoop.hpp"
#include "SFML/Graphics.hpp"

int main()
{
    GameLoop* game = new GameLoop();
    game->start();
    delete game;

    return 0;
}
