#ifndef AIFEST_GAME_H
#define AIFEST_GAME_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "Grid.h"

class Game {
private:
    sf::Vector2f _gridSize;
    sf::Vector2f _tileSize;
    sf::Vector2f _screenSize;

    Grid* _grid;

public:
    Game(sf::Vector2f screenSize, sf::Vector2f gridSize, sf::Vector2f tileSize);
    ~Game();

    void Init();
    void Draw(sf::RenderWindow* window);
    void SetMousePosition(sf::Vector2i position);
};


#endif //AIFEST_GAME_H
