#include "AbstractElement.hpp"

void AbstractElement::render(sf::RenderWindow *window) {
    shape->setFillColor(sf::Color(140, 42, 0));
    shape->setPosition(this->coords.toVector2f());
    // shape->setOrigin(this->coords.toVector2f());

    window->draw(*this->shape);
}

AbstractElement::~AbstractElement() {
}
