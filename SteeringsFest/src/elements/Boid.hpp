#ifndef AIFEST_BOID_HPP
#define AIFEST_BOID_HPP


#include "DynamicElement.hpp"

class Boid : public DynamicElement {
public:
    Boid(const Vector2& coords);

    Vector2 followPath(const Track* track);

    virtual Vector2 applyForce(const Track* track) override;
    virtual void update(const Track* track, const std::vector<Boid*>& elements);
};


#endif //AIFEST_BOID_HPP
