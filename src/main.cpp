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
        }

        window.clear(sf::Color::Black);

        scene.draw(&window);

        window.display();
    }

    return EXIT_SUCCESS;
}