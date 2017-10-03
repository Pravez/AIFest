#ifndef STEERINGSFEST_VEHICLE_HPP
#define STEERINGSFEST_VEHICLE_HPP


#include <SFML/Graphics/Color.hpp>
#include "utils.hpp"
#include "Track.hpp"

class Vehicle {
private:
    Vector2 coords;
    Vector2 speed;
    int maxSpeed;
    Vector2 force;
    int maxForce;
    sf::Color color = sf::Color(42, 142, 242, 255);
    sf::Color fgColor;
    int radius = 6;
    int seeInFuture = 3;

public:
    Vehicle(Vector2 coords = {0, 0}, Vector2 speed = {1, 1}, Vector2 force = {1, 1}) :
        coords(coords), speed(speed), force(force) {}
    ~Vehicle();

    Vector2 steerPathFollow(const Track* track);

    void draw(sf::RenderWindow* window);

    void steerSeparation(Vehicle vehicles[]);

    Vector2 getCoords() const { return this->coords; }
    int getRadius() const { return this->radius; }
    Vector2 getSpeed() const { return this->speed; }
    Vector2 getForce() const { return this->force; }
    int getMaxSpeed() const { return this->maxSpeed; }
    int getMaxForce() const { return this->maxForce; }


    void setCoords(Vector2 coords) { this->coords.setX(coords.getX()); this->coords.setY(coords.getY()); }
    void setSpeed(Vector2 speed) { this->speed = speed; }
};


#endif //STEERINGSFEST_VEHICLE_HPP
