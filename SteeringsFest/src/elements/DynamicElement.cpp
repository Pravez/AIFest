#include "DynamicElement.hpp"

DynamicElement::DynamicElement(sf::Shape *shape, const Vector2 &coords, int radius, const Vector2 &speed,
                               const Vector2 &force,
                               int seeInFuture) :
        AbstractElement(shape, coords), radius(radius), speed(speed), seeInFuture(seeInFuture) {}

void DynamicElement::update(const Track *track) {
    this->force.set(0);
    this->force.add(this->applyForce(track));
}

void DynamicElement::render(sf::RenderWindow *window) {
    AbstractElement::render(window);

    sf::Vertex line[] = {
            sf::Vertex(Vector2::diff(this->getCoords(), Vector2(this->radius / 2, this->radius / 2)).toVector2f()),
            sf::Vertex(Vector2::add(this->speed, this->getCoords()).scalar(1)->toVector2f())
    };

    window->draw(line, 2, sf::Lines);
}
