#ifndef STEERINGSFEST_TRACK_HPP
#define STEERINGSFEST_TRACK_HPP


#include <vector>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "utils.hpp"

struct SegmentAndPoint {
    SegmentAndPoint(int segment, Vector2 point): segment(segment), point(point) {}

    int segment;
    Vector2 point;
};

struct PredictivePosition {
    PredictivePosition(int segment, Vector2 point, double length): segment(segment), point(point), length(length) {}

    int segment;
    Vector2 point;
    double length;
};

class Track {
private:
    std::vector<Vector2> circuit;
    std::vector<double> cachedLength;
    std::vector<Vector2> cachedNormal;
    sf::Color backColor;
    sf::Color color;
    int width = 30;

public:
    Track(Vector2 circuit[], int size);
    ~Track();

    void draw(sf::RenderWindow* window);
    SegmentAndPoint segmentPointAddLength(int segment, Vector2 point, int length) const;
    PredictivePosition closestSegmentPointToPoint(Vector2 point) const;
    Vector2 closestPointToSegment(int segment, Vector2 point) const;

};

#endif //STEERINGSFEST_TRACK_HPP
