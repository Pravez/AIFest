#include <SFML/Graphics/CircleShape.hpp>
#include "Vehicle.hpp"

Vector2 Vehicle::steerPathFollow(const Track *track) {
    PredictivePosition predicted = track->closestSegmentPointToPoint(this->coords);
    SegmentAndPoint futurePositionAndSegment =
            track->segmentPointAddLength(predicted.segment,
                                         predicted.point,
                                         static_cast<int>(max(10,
                                                              this->speed.approximateLength()) *
                                                          this->seeInFuture));
    Vector2 force = Vector2::diff(futurePositionAndSegment.point, this->coords);
    force.scalar(this->maxForce / force.approximateLength());
    return force;
}

void Vehicle::draw(sf::RenderWindow *window) {
    sf::CircleShape shape;
    shape.setFillColor(this->color);
    shape.setPosition(this->coords.toVector2f());
    shape.setRadius(this->radius);

    sf::Vertex line[] = {
            sf::Vertex(Vector2::diff(this->coords, Vector2(this->radius/2, this->radius/2)).toVector2f()),
            sf::Vertex(Vector2::add(this->speed, this->coords).scalar(1)->toVector2f())
    };

    window->draw(shape);
    window->draw(line, 2, sf::Lines);
}

Vehicle::~Vehicle() {
}

void Vehicle::update(Track *track, std::vector<Vehicle*> vehicles) {
    this->force = Vector2(0, 0);
    this->force.add(this->steerPathFollow(track));
    // this->steerSeparation(vehicles);
}


