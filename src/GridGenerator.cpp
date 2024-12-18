#include "GridGenerator.h"

GridGenerator::GridGenerator(int width, int height, float obstacleDensity)
    : width(width), height(height), obstacleDensity(obstacleDensity) {
    std::srand(std::time(nullptr)); // Inizializza il generatore di numeri casuali
}

GridGenerator::~GridGenerator() {}

std::vector<std::vector<int>> GridGenerator::generateGrid() {
    std::vector<std::vector<int>> grid(height, std::vector<int>(width, 0));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[y][x] = isObstacle() ? 1 : 0; // 1 = ostacolo, 0 = spazio libero
        }
    }
    return grid;
}

void GridGenerator::printGrid(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell == 1) {
                std::cout << "█ "; // Ostacolo
            } else {
                std::cout << ". "; // Spazio libero
            }
        }
        std::cout << "\n";
    }
}

bool GridGenerator::isObstacle() const {
    return static_cast<float>(std::rand()) / RAND_MAX < obstacleDensity;
}
