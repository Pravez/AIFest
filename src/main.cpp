#include <SFML/Graphics.hpp>
#include "Scene.hpp"

int main(int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Steerings");

    Vector2 vectors[] = {
            Vector2(200, 200),
            Vector2(200, 400),
            Vector2(400, 400),
            Vector2(400, 200)
    };

    Scene scene(vectors, 4);

    window.setFramerateLimit(24);
    window.setVerticalSyncEnabled(true);

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Right) {
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