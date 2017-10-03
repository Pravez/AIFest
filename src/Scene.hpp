//
// Created by howl on 03/10/17.
//

#ifndef STEERINGSFEST_SCENE_HPP
#define STEERINGSFEST_SCENE_HPP


#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Vehicle.hpp"
#include "Track.hpp"

class Scene {
private:
    std::vector<Vehicle> vehicles;
    Track track;

public:
    Scene(Vector2 circuit[], int size);
    ~Scene();

    void addVehicle(int x, int y);

    void handleVehiclesCollisions();
    void updateVehiclesPositions();

    void update();
    void draw(sf::RenderWindow* window);
};


#endif //STEERINGSFEST_SCENE_HPP
