//
// Created by Utente on 25/09/2025.
//

#include "Map.h"
#include <iostream>
#include  <SFML/Graphics.hpp>
#include <SFML/graphics/Texture.hpp>

Map::Map(int width, int height, int tileSize) : tileSize(tileSize) {
    grid.resize(height, std::vector<int>(width, 0));

    // Crea alcuni ostacoli
    for (int i = 2; i < width - 2; i += 3) {
        for (int j = 2; j < height - 2; j += 2) {
            if (rand() % 3 == 0) { // 33% di chance di ostacolo
                grid[j][i] = 1;
            }
        }
    }
}

void Map::loadTextures() {
    // Texture semplici (puoi sostituire con immagini reali)
    wallTexture.loadFromFile("wall.png");
    groundTexture.loadFromFile("ground.png");}

void Map::draw(sf::RenderWindow& window) {
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[0].size(); ++x) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
            if (grid[y][x] == 1) { // Muro
                tile.setFillColor(sf::Color(100, 100, 100));
            } else { // Terreno
                tile.setFillColor(sf::Color(200, 200, 150));
            }

            tile.setOutlineThickness(1);
            tile.setOutlineColor(sf::Color(50, 50, 50));
            window.draw(tile);
        }
    }
}

bool Map::isWalkable(int x, int y) const {
    if (x < 0 || y < 0 || x >= grid[0].size() || y >= grid.size()) {
        return false;
    }
    return grid[y][x] == 0;
}

sf::Vector2i Map::getGridSize() const {
    return sf::Vector2i(grid[0].size(), grid.size());
}

int Map::getTileSize() const {
    return tileSize;
}

const std::vector<std::vector<int>>& Map::getGrid() const {
    return grid;
}

void Map::setTile(int x, int y, int value) {
    if (x >= 0 && y >= 0 && x < grid[0].size() && y < grid.size()) {
        grid[y][x] = value;
    }
}
