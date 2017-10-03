//
// Created by howl on 03/10/17.
//

#include "Scene.hpp"

void Scene::draw(sf::RenderWindow* window) {
    this->track.draw(window);
}

Scene::Scene(Vector2 circuit[], int size): track(Track(circuit, size)){

}

Scene::~Scene() {

}
