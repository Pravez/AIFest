#ifndef AIFEST_DYNAMICELEMENT_HPP
#define AIFEST_DYNAMICELEMENT_HPP


#include "AbstractElement.hpp"

class DynamicElement : public AbstractElement {
private:
    int radius;
    Vector2 speed;
    Vector2 force;
    int seeInFuture;

public:
    DynamicElement(sf::Shape* shape, const Vector2& coords, int radius = 6, const Vector2& speed = {1, 1}, const Vector2& force = {0, 0},
                   int seeInFuture = 3);

    int getRadius() { return radius; }
    const Vector2& getSpeed() { return speed; }
    void setSpeed(const Vector2& speed) { this->speed = speed; }
    const Vector2& getForce() { return force; }
    int getSeeInFuture() { return seeInFuture; }

    virtual Vector2 applyForce(const Track* track) = 0;
    virtual void update(const Track* track) override;
    virtual void render(sf::RenderWindow* window) override;

    static const int MAXSPEED = 10;
    static const int MAXFORCE = 10;
};


#endif //AIFEST_DYNAMICELEMENT_HPP
