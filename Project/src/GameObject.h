#ifndef AIFEST_GAMEOBJECT_H
#define AIFEST_GAMEOBJECT_H

#include <SFML/System.hpp>

class GameObject {
private:
    sf::Vector2f _position;

public:
    GameObject();

    void SetPosition(sf::Vector2f position) { _position = position; }
    sf::Vector2f GetPosition() { return _position; }
};


#endif //AIFEST_GAMEOBJECT_H
