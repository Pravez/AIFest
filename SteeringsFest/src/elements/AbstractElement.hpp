#ifndef AIFEST_ABSTRACTELEMENT_HPP
#define AIFEST_ABSTRACTELEMENT_HPP


#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../utils.hpp"
#include "../Track.hpp"

class AbstractElement {
private:
    sf::Shape* shape;
    Vector2 coords;
    sf::Color color;

public:
    AbstractElement(sf::Shape* shape, const Vector2& coords = {0, 0},
                    sf::Color color = sf::Color(42, 242, 42)): coords(coords), color(color), shape(shape) {}

    virtual ~AbstractElement();

    void setCoords(const Vector2& coords) { this->coords = coords; }
    virtual const Vector2& getCoords() const { return this->coords; }
    void setColor(const sf::Color& color) { this->color = color; }

    virtual void render(sf::RenderWindow* window);
    virtual void update(const Track *track) = 0;
};


#endif //AIFEST_ABSTRACTELEMENT_HPP
