//
// Created by howl on 03/10/17.
//

#include "Scene.hpp"

void Scene::draw(sf::RenderWindow *window) {
    this->track.draw(window);

    for (auto vehicle : this->vehicles) {
        vehicle->draw(window);
    }
}

Scene::Scene(Vector2 circuit[], int size) : track(Track(circuit, size)) {

}

Scene::~Scene() {

}

void Scene::update() {
    for(auto v: vehicles) {
        v->update(&this->track, this->vehicles);
    }

    this->updateVehiclesPositions();
    this->handleVehiclesCollisions();
}

void Scene::handleVehiclesCollisions() {
    Vector2 offset;
    double approximateLength;
    double tempCompute;

    for (int i = 0; i < this->vehicles.size(); ++i) {
        for (auto v : this->vehicles) {
            offset = Vector2::diff(v->getCoords(), this->vehicles[i]->getCoords());
            approximateLength = offset.approximateLength();
            if (approximateLength != 0 &&
                approximateLength < this->vehicles[i]->getRadius() + v->getRadius() - 1) {
                tempCompute = approximateLength * (this->vehicles[i]->getRadius() + v->getRadius());
                this->vehicles[i]->setCoords(
                        Vector2(
                                this->vehicles[i]->getCoords().getX() + offset.getX() / tempCompute,
                                this->vehicles[i]->getCoords().getY() + offset.getY() / tempCompute));
            }
        }
    }
}

void Scene::updateVehiclesPositions() {
    for(auto v : this->vehicles) {
        v->setSpeed(Vector2::add(v->getSpeed(), v->getForce()));
        double approximateLength = v->getSpeed().approximateLength();
        if (approximateLength > v->getMaxSpeed()) {
            v->setSpeed(Vector2::scalar(v->getSpeed(), v->getMaxSpeed() / approximateLength));
        }
        v->setCoords(Vector2(v->getCoords().getX() + v->getSpeed().getX(), v->getCoords().getY() + v->getSpeed().getY()));
    }

}

void Scene::addVehicle(int x, int y) {
    this->vehicles.push_back(new Vehicle(Vector2(x, y)));
    printf("Added vehicle at %d, %d\n", x, y);
}
