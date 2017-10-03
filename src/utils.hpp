#ifndef STEERINGSFEST_VECTOR2_HPP
#define STEERINGSFEST_VECTOR2_HPP

#include <SFML/System.hpp>

class Vector2 {
private:
    double x, y;

public:
    static Vector2 diff(Vector2 v1, Vector2 v2);
    static Vector2 add(Vector2 v1, Vector2 v2);
    static Vector2 scalar(Vector2 v1, double scalar);

    Vector2(double x, double y) : x(x), y(y) {}
    Vector2(const Vector2& v): x(v.x), y(v.y) {}
    Vector2(): x(0), y(0) {}

    Vector2* diff(Vector2 vec);
    Vector2* add(Vector2 vec);
    Vector2* scalar(int scal);
    double dot(Vector2 vec) const;
    Vector2* inter(int scalar, Vector2 vec);
    double approximateLength() const;
    double approximateDistanceWith(Vector2 vec) const;
    Vector2 getPerpendicular() const;

    double getX() const;
    void setX(double x);
    double getY() const;
    void setY(double y);

    sf::Vector2f toVector2f() const;

};

double max(double first, double second);

#endif //STEERINGSFEST_VECTOR2_HPP
