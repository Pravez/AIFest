#ifndef AIFEST_GRID_H
#define AIFEST_GRID_H


#include "Tile.h"
#include <SFML/Graphics/VertexArray.hpp>

class Grid {
private:
    sf::Vector2f _size;
    sf::Vector2f _tileSize;
    Tile** _grid;

    sf::VertexArray** _graphicGrid;
    sf::Vector2f _activatedTile;

public:
    Grid(sf::Vector2f size, sf::Vector2f tileSize);
    ~Grid();

    void InitGraphics();

    void PlaceOnTile(const sf::Vector2f& tile, const GameObject* object);
    void DrawGrid(sf::RenderWindow *window);
    void DrawTiles(sf::RenderWindow* window);

    void ActivateTile(sf::Vector2f position);
};


#endif //AIFEST_GRID_H
