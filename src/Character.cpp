#include "Character.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Character::Character(float radius, sf::Color color) :
    speed(100.0f),
    isMoving(false),
    currentPathIndex(0),
    position(0, 0),
    targetPosition(0, 0) {

    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
}

void Character::setPosition(const sf::Vector2f& pos) {
    position = pos;
    shape.setPosition(position);
}

void Character::setTarget(const sf::Vector2f& target, const std::vector<std::vector<int>>& grid) {
    stop();

    // Converti coordinate pixel a coordinate griglia
    int startX = static_cast<int>(position.x / 50);
    int startY = static_cast<int>(position.y / 50);
    int endX = static_cast<int>(target.x / 50);
    int endY = static_cast<int>(target.y / 50);

    // Controlla che le coordinate siano valide
    if (startX >= 0 && startY >= 0 &&
        endX >= 0 && endY >= 0 &&
        endX < static_cast<int>(grid[0].size()) &&
        endY < static_cast<int>(grid.size()) &&
        grid[endY][endX] == 0) {

        Node start(startX, startY);
        Node end(endX, endY);

        path = AStar::findPath(grid, start, end);

        if (!path.empty()) {
            currentPathIndex = 0;
            isMoving = true;
            targetPosition = sf::Vector2f(path[0].x * 50 + 25, path[0].y * 50 + 25);
        }
    }
}

void Character::update(float deltaTime) {
    if (!isMoving || path.empty() || currentPathIndex >= path.size())
        return;

    // Prendi il prossimo nodo del percorso
    Node nextNode = path[currentPathIndex];
    sf::Vector2f targetPixelPos(nextNode.x * 50 + 25, nextNode.y * 50 + 25);

    // Calcola la direzione e la distanza
    sf::Vector2f direction = targetPixelPos - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 2.0f) {
        // Se siamo abbastanza vicini, passa al prossimo nodo
        position = targetPixelPos;
        currentPathIndex++;

        // Controlla se abbiamo raggiunto la fine del percorso
        if (currentPathIndex >= path.size()) {
            isMoving = false;
        }
    } else {
        // Normalizza la direzione e muovi il character
        direction /= distance;
        position += direction * speed * deltaTime;
    }

    shape.setPosition(position);
}

void Character::draw(sf::RenderWindow& window) {
    window.draw(shape);

    // Disegna il percorso con linee verdi
    if (!path.empty()) {
        for (size_t i = 0; i < path.size() - 1; ++i) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(path[i].x * 50 + 25, path[i].y * 50 + 25), sf::Color::Green),
                sf::Vertex(sf::Vector2f(path[i+1].x * 50 + 25, path[i+1].y * 50 + 25), sf::Color::Green)
            };
            window.draw(line, 2, sf::Lines);
        }
    }
}

void Character::stop() {
    isMoving = false;
    path.clear();
    currentPathIndex = 0;
}

sf::Vector2f Character::getPosition() const {
    return position;
}

bool Character::getIsMoving() const {
    return isMoving;
}