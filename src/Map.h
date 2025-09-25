//
// Created by Utente on 25/09/2025.
//

#define CMAKESFMLPROJECT_MAP_H
#pragma once
#include <SFML/graphics/Texture.hpp>

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
private:
    std::vector<std::vector<int>> grid;
    int tileSize;
    sf::Texture wallTexture;
    sf::Texture groundTexture;

public:
    Map(int width, int height, int tileSize = 50);

    void loadTextures();
    void draw(sf::RenderWindow& window);
    bool isWalkable(int x, int y) const;
    sf::Vector2i getGridSize() const;
    int getTileSize() const;
    const std::vector<std::vector<int>>& getGrid() const;

    void setTile(int x, int y, int value);
};

