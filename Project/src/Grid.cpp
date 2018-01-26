#include <SFML/Graphics/RenderWindow.hpp>
#include "Grid.h"

Grid::Grid(sf::Vector2f size, sf::Vector2f tileSize) {
    _size = size;
    _tileSize = tileSize;

    _grid = new Tile*[(int)size.x];
    for(int i = 0;i < size.x; ++i) {
        _grid[i] = new Tile[(int)size.y];
        for(int j = 0;j < size.y; ++j) {
            _grid[i][j].SetPosition({i, j});
            _grid[i][j].SetSize(tileSize);
        }
    }

    _activatedTile = {0, 0};
    _grid[(int) _activatedTile.x][(int) _activatedTile.y].ToggleActivate();
}

Grid::~Grid() {
    for(int i = 0;i < _size.x; ++i)
        delete[] _grid[i];
    delete[] _grid;
}

void Grid::PlaceOnTile(const sf::Vector2f &tile, const GameObject *object) {
    _grid[(int) tile.x][(int) tile.y].SetObject(object);
}

void Grid::DrawGrid(sf::RenderWindow *window) {
    for(int i = 0;i < _size.x; ++i) {
        for(int j = 0;j < _size.y; ++j) {
            window->draw(_graphicGrid[i][j]);
        }
    }
}

void Grid::InitGraphics() {
    _graphicGrid = new sf::VertexArray*[(int)_size.x];
    for(int i = 0;i < _size.x; ++i) {
        _graphicGrid[i] = new sf::VertexArray[(int)_size.y];
        for(int j = 0;j < _size.y; ++j) {
            sf::VertexArray cell;
            cell = sf::VertexArray(sf::LinesStrip, 4);
            cell[0].position = sf::Vector2f(i*_tileSize.x, j*_tileSize.y);
            cell[1].position = sf::Vector2f((i+1)*_tileSize.x, j*_tileSize.y);
            cell[2].position = sf::Vector2f((i+1)*_tileSize.x, (j+1)*_tileSize.y);
            cell[3].position = sf::Vector2f(i*_tileSize.x, (j+1)*_tileSize.y);

            cell[0].color = sf::Color::White;
            cell[1].color = sf::Color::White;
            cell[2].color = sf::Color::White;
            cell[3].color = sf::Color::White;

            _graphicGrid[i][j] = cell;
        }
    }
}

void Grid::ActivateTile(sf::Vector2f position) {
    _grid[(int) _activatedTile.x][(int) _activatedTile.y].ToggleActivate();
    _activatedTile = position;
    _grid[(int) _activatedTile.x][(int) _activatedTile.y].ToggleActivate();
}

void Grid::DrawTiles(sf::RenderWindow* window) {
    for(int i = 0;i < _size.x; ++i) {
        for(int j = 0;j < _size.y; ++j) {
            _grid[i][j].Draw(window);
        }
    }
}





