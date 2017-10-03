#include <cmath>
#include "utils.hpp"


Vector2* Vector2::diff(Vector2 vec) {
    this->x -= vec.x;
    this->y -= vec.y;
    return this;
}

Vector2* Vector2::add(Vector2 vec) {
    this->x += vec.x;
    this->y += vec.y;
    return this;
}

Vector2* Vector2::scalar(int scal) {
    this->x *= scal;
    this->y *= scal;
    return this;
}

double Vector2::dot(Vector2 vec) const {
    return this->x * vec.x + this->y * vec.y;
}

Vector2* Vector2::inter(int scalar, Vector2 vec) {
    this->x = this->x + scalar * (vec.x - this->x);
    this->y += scalar * (vec.y - vec.x);
    return this;
}

Vector2 Vector2::diff(Vector2 v1, Vector2 v2) {
    return Vector2(v1.x - v2.x, v1.y - v2.y);
}

double Vector2::approximateLength() const {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

double Vector2::approximateDistanceWith(Vector2 vec) const {
    return (Vector2::diff(*this, vec)).approximateLength();
}

Vector2 Vector2::add(Vector2 v1, Vector2 v2) {
    return Vector2(v1.x + v2.x, v1.y + v2.y);
}

double Vector2::getX() const {
    return x;
}

void Vector2::setX(int x) {
    Vector2::x = x;
}

double Vector2::getY() const {
    return y;
}

void Vector2::setY(int y) {
    Vector2::y = y;
}

sf::Vector2f Vector2::toVector2f() const {
    return sf::Vector2f(static_cast<float>(this->x), static_cast<float>(this->y));
}

Vector2 Vector2::getPerpendicular() const {
    return Vector2(this->y, - this->x);
}


