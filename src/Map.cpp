#include "Map.h"
#include <cstdlib>
#include <ctime>

Map::Map(int rows, int cols, int tileSize, float obstacleDensity)
    : rows(rows), cols(cols), tileSize(tileSize) {
    std::srand(std::time(nullptr));
    generateGrid(obstacleDensity);
}

Map::~Map() {
    for (auto& row : tiles) {
        for (auto& tile : row) {
            delete tile;
        }
    }
}

void Map::generateGrid(float obstacleDensity) {
    for (int y = 0; y < rows; ++y) {
        std::vector<Tile*> tileRow;
        std::vector<int> gridRow;
        for (int x = 0; x < cols; ++x) {
            bool isObstacle = (static_cast<float>(std::rand()) / RAND_MAX) < obstacleDensity;
            tileRow.push_back(new Tile(x * tileSize, y * tileSize, tileSize, isObstacle));
            gridRow.push_back(isObstacle ? 1 : 0); // 1 = ostacolo, 0 = libero
        }
        tiles.push_back(tileRow);
        grid.push_back(gridRow);
    }
}

void Map::render(SDL_Renderer* renderer) {
    for (auto& row : tiles) {
        for (auto& tile : row) {
            tile->render(renderer);
        }
    }
}

const std::vector<std::vector<int>>& Map::getGrid() const {
    return grid;
}
