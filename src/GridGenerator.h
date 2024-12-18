#ifndef GRIDGENERATOR_H
#define GRIDGENERATOR_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

class GridGenerator {
public:
    GridGenerator(int width, int height, float obstacleDensity);
    ~GridGenerator();

    std::vector<std::vector<int>> generateGrid();
    void printGrid(const std::vector<std::vector<int>>& grid);

private:
    int width;
    int height;
    float obstacleDensity; // Percentuale di celle con ostacoli (0.0 - 1.0)

    bool isObstacle() const; // Determina se una cella è un ostacolo
};

#endif
