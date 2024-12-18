#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <vector>

class Map {
public:
    Map(int rows, int cols, int tileSize, float obstacleDensity);
    ~Map();

    void render(SDL_Renderer* renderer);
    const std::vector<std::vector<int>>& getGrid() const; // Metodo per ottenere la griglia

private:
    int rows, cols, tileSize;
    std::vector<std::vector<Tile*>> tiles; // Griglia delle Tile
    std::vector<std::vector<int>> grid;    // Rappresentazione numerica della griglia

    void generateGrid(float obstacleDensity);
};

#endif
