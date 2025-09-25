#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "Character.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pathfinding con A*");
    window.setFramerateLimit(60);

    // Crea mappa 16x12
    Map map(16, 12);
    map.loadTextures();

    Character player;

    // Posizione iniziale del player
    player.setPosition(sf::Vector2f(100, 100));

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    player.setTarget(sf::Vector2f(mousePos.x, mousePos.y), map.getGrid());
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Space)
                    player.stop();
            }
        }

        player.update(deltaTime);

        window.clear(sf::Color::Black);
        map.draw(window);
        player.draw(window);
        window.display();
    }

    return 0;
}

