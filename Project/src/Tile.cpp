#include <SFML/Graphics/VertexArray.hpp>
#include "Tile.h"

void Tile::Draw(sf::RenderWindow* window) {
    if(_activated) {
        DrawInCell(window, sf::Color::Red);
    }
}

bool Tile::IsActivated() const {
    return _activated;
}

void Tile::DrawInCell(sf::RenderWindow *window, sf::Color color) {
    sf::VertexArray quad(sf::Quads, 4);

    quad[0].position = sf::Vector2f(_position.x * _size.x, _position.y*_size.y);
    quad[1].position = sf::Vector2f((_position.x+1) * _size.x-1, _position.y*_size.y);
    quad[2].position = sf::Vector2f((_position.x+1) * _size.x-1, (_position.y+1)*_size.y-1);
    quad[3].position = sf::Vector2f(_position.x * _size.x, (_position.y+1)*_size.y-1);

    quad[1].color = color;
    quad[0].color = color;
    quad[2].color = color;
    quad[3].color = color;

    window->draw(quad);
}
