#include <SFML/Graphics.hpp>
#include "Scene.hpp"

int main(int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Steerings");

    Vector2 vectors[] = {
            Vector2(50, 100),
            Vector2(300, 100),
            Vector2(400, 400),
            Vector2(500, 500),
            Vector2(600, 500),
            Vector2(300, 250)
    };

    Scene scene(vectors, 6);

    window.setFramerateLimit(24);
    window.setVerticalSyncEnabled(true);

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    scene.addVehicle(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        window.clear(sf::Color::Black);

        scene.update();
        scene.draw(&window);

        window.display();
    }

    return EXIT_SUCCESS;
}