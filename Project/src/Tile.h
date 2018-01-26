#ifndef AIFEST_TILE_H
#define AIFEST_TILE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"

class Tile {
private:
    sf::Vector2f _position;
    sf::Vector2f _size;
    const GameObject *_currentObject;

    bool _activated;

public:
    Tile(): _position({0, 0}), _size({0, 0}), _activated(false) {}
    Tile(sf::Vector2f size): _position({0, 0}), _size(size), _activated(false) {}
    Tile(sf::Vector2f position, sf::Vector2f size): _position(position), _size(size), _activated(false) {}

    void SetPosition(const sf::Vector2f &_position) {
        Tile::_position = _position;
    }

    void SetObject(const GameObject* object) { _currentObject = object; }

    void SetSize(const sf::Vector2f &_size) {
        Tile::_size = _size;
    }
    void ToggleActivate() { _activated = !_activated; };

    bool IsActivated() const;

    void Draw(sf::RenderWindow* window);
    void DrawInCell(sf::RenderWindow* window, sf::Color color);
};


#endif //AIFEST_TILE_H
