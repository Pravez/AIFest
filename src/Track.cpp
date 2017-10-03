#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include "Track.hpp"

Track::Track(Vector2 circuit[], int size) {
    this->backColor = sf::Color(128, 128, 128, 255);
    this->color = sf::Color(10, 10, 10, 255);

    for (int i = 0; i < size; i++) {
        this->circuit.push_back(circuit[i]);
        this->cachedNormal.push_back(Vector2::diff(circuit[i], i - 1 < 0 ? circuit[size] : circuit[i - 1]));
        this->cachedLength.push_back(this->cachedNormal[i].approximateLength());
        this->cachedNormal[i] = Vector2(this->cachedNormal[i].getX() / this->cachedLength[i],
                                        this->cachedNormal[i].getY() / this->cachedLength[i]);
    }
}

Track::~Track() {

}

void Track::draw(sf::RenderWindow *window) {
    sf::CircleShape edge;
    edge.setFillColor(this->backColor);

    sf::ConvexShape convex;
    convex.setPointCount(4);
    convex.setFillColor(this->backColor);

    for (int i = 0; i < this->circuit.size(); i++) {
        edge.setPosition(Vector2(this->circuit[i]).diff(Vector2(this->width / 2, this->width / 2))->toVector2f());
        edge.setRadius(this->width / 2);

        sf::Vertex line[] = {
                sf::Vertex(i - 1 < 0 ? this->circuit[this->circuit.size() - 1].toVector2f() :
                           this->circuit[i - 1].toVector2f()),
                sf::Vertex(this->circuit[i].toVector2f())
        };

        window->draw(edge);
        window->draw(line, 2, sf::Lines);
    }


}

SegmentAndPoint Track::segmentPointAddLength(int segment, Vector2 point, int length) const {
    double nextStep = this->circuit[segment].approximateDistanceWith(point);
    Vector2 nextPoint;

    if (nextStep > length) {
        nextPoint = (Vector2::add(point, Vector2::scalar(this->cachedNormal[segment], length)));
        return SegmentAndPoint(segment, nextPoint);
    }

    length -= nextStep;
    segment = segment + 1 < this->circuit.size() ? segment + 1 : 0;
    while (length > this->cachedLength[segment]) {
        length -= this->cachedLength[segment];
        segment = segment + 1 < this->circuit.size() ? segment + 1 : 0;
    }
    nextPoint = Vector2::add(this->circuit[segment - 1 < 0 ? this->circuit.size() - 1 : segment - 1],
                             Vector2::scalar(this->cachedNormal[segment], length));
    return SegmentAndPoint(segment, nextPoint);
}

PredictivePosition Track::closestSegmentPointToPoint(Vector2 point) const {
    int bestSegment = 0;
    Vector2 bestPoint, temp;
    double bestLength = -1, l;

    for(int i = 0;i < this->circuit.size(); ++i) {
        temp = this->closestPointToSegment(i, point);
        l = temp.approximateDistanceWith(point);
        if (bestLength == -1 || l < bestLength) {
            bestLength = l;
            bestPoint = temp;
            bestSegment = i;
        }
    }

    return PredictivePosition(bestSegment, bestPoint, bestLength);
}

Vector2 Track::closestPointToSegment(int segment, Vector2 point) const {
    Vector2 firstPosition = this->circuit[segment - 1 < 0 ? this->circuit.size() - 1 : segment - 1];
    Vector2 secondPosition = this->circuit[segment];
    Vector2 local = Vector2::diff(point, firstPosition);
    double projection = local.dot(this->cachedNormal[segment]);
    if (projection < 0) {
        return firstPosition;
    } else if (projection > this->cachedLength[segment]) {
        return secondPosition;
    } else {
        return Vector2::add(firstPosition, Vector2::scalar(this->cachedNormal[segment], projection));
    }
}

