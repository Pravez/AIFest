#include "Game.h"

Game::Game(sf::Vector2f screenSize, sf::Vector2f gridSize, sf::Vector2f tileSize) {
    _grid = new Grid(gridSize, tileSize);
    _gridSize = gridSize;
    _tileSize = tileSize;
    _screenSize = screenSize;
}

Game::~Game() {
    delete _grid;
}

void Game::Init() {
    _grid->InitGraphics();
}

void Game::Draw(sf::RenderWindow *window) {
    _grid->DrawGrid(window);
    _grid->DrawTiles(window);
}

void Game::SetMousePosition(sf::Vector2i position) {
    if (position.x >= 0 && position.x < _screenSize.x && position.y >= 0 && position.y < _screenSize.y)
        _grid->ActivateTile(sf::Vector2f(position.x / _tileSize.x, position.y / _tileSize.y));
}
