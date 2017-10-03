#include <SFML/Graphics.hpp>
#include "Scene.hpp"

int main(int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Steerings");

    Vector2 vectors[] = {
            Vector2(10, 10),
            Vector2(20, 20),
            Vector2(35, 75),
            Vector2(600, 380),
            Vector2(550, 40)
    };

    Scene scene(vectors, 5);

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