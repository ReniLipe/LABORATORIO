#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "AStar.h"  // Assumendo che tu abbia una classe AStar con Node

class Character {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    float speed;
    bool isMoving;
    std::vector<Node> path;
    size_t currentPathIndex;
    sf::Vector2f targetPosition;

public:
    Character(float radius = 20.0f, sf::Color color = sf::Color::Red);
    
    void setPosition(const sf::Vector2f& pos);
    void setTarget(const sf::Vector2f& target, const std::vector<std::vector<int>>& grid);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void stop();
    
    sf::Vector2f getPosition() const;
    bool getIsMoving() const;
};

#endif