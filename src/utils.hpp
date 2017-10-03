//
// Created by howl on 03/10/17.
//

#ifndef STEERINGSFEST_VECTOR2_HPP
#define STEERINGSFEST_VECTOR2_HPP

#include <SFML/System.hpp>

class Vector2 {
private:
    double x, y;

public:
    static Vector2 diff(Vector2 v1, Vector2 v2);
    static Vector2 add(Vector2 v1, Vector2 v2);

    Vector2(double x, double y) : x(x), y(y) {}

    Vector2* diff(Vector2 vec);
    Vector2* add(Vector2 vec);
    Vector2* scalar(int scal);
    double dot(Vector2 vec) const;
    Vector2* inter(int scalar, Vector2 vec);
    double approximateLength() const;
    double approximateDistanceWith(Vector2 vec) const;
    Vector2 getPerpendicular() const;

    double getX() const;
    void setX(int x);
    double getY() const;
    void setY(int y);

    sf::Vector2f toVector2f() const;

};


#endif //STEERINGSFEST_VECTOR2_HPP
