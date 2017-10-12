#include <SFML/Graphics/CircleShape.hpp>
#include "Boid.hpp"

Boid::Boid(const Vector2 &coords) : DynamicElement(new sf::CircleShape(), coords) {
}

Vector2 Boid::applyForce(const Track *track) {
    return followPath(track);
}

Vector2 Boid::followPath(const Track *track) {
    PredictivePosition predicted = track->closestSegmentPointToPoint(this->getCoords());
    SegmentAndPoint futurePositionAndSegment =
            track->segmentPointAddLength(predicted.segment,
                                         predicted.point,
                                         static_cast<int>(max(10,
                                                              this->getSpeed().approximateLength()) *
                                                          this->getSeeInFuture()));
    Vector2 force = Vector2::diff(futurePositionAndSegment.point, this->getCoords());
    force.scalar(this->MAXFORCE / force.approximateLength());
    return force;
}

void Boid::update(const Track *track, const std::vector<Boid*> &elements) {
    DynamicElement::update(track);
}