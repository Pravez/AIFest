#ifndef AIFEST_ABSTRACTELEMENT_HPP
#define AIFEST_ABSTRACTELEMENT_HPP


#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../utils.hpp"
#include "../Track.hpp"

class AbstractElement {
private:
    Vector2 coords;
    sf::Shape* shape;
    sf::Color color;

public:
    AbstractElement(const Vector2& coords = {0, 0}, sf::Color color = sf::Color(255, 255, 0)): coords(coords), color(color);
    ~AbstractElement();

    void setShape(sf::Shape* shape) { this->shape = shape; }
    void setCoords(const Vector2& coords) { this->coords = coords; }
    const Vector2& getCoords() const { return this->coords; }
    void setColor(const sf::Color& color) { this->color = color; }

    virtual void render(sf::RenderWindow* window);
    virtual void update(const Track *track) = 0;
};


#endif //AIFEST_ABSTRACTELEMENT_HPP
