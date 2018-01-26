#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main() {
    sf::Vector2f screenSize = {800, 600}, tileSize = {10, 10}, gridSize = {screenSize.x / tileSize.x,
                                                                      screenSize.y / tileSize.y};

    // create the window
    sf::RenderWindow window(
            sf::VideoMode(static_cast<unsigned int>(screenSize.x), static_cast<unsigned int>(screenSize.y)),
            "IA - Project");

    Game game(screenSize, gridSize, tileSize);
    game.Init();
    sf::Vector2i mousePosition;

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        mousePosition = sf::Mouse::getPosition(window);
        printf("(%d, %d)\n", mousePosition.x, mousePosition.y);

        // draw everything here...
        // window.draw(...);
        game.SetMousePosition(mousePosition);
        game.Draw(&window);

        // end the current frame
        window.display();
    }

    return 0;
}