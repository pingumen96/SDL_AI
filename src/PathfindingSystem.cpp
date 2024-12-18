#include "PathfindingSystem.h"
#include <algorithm>
#include <queue>
#include <map>
#include <cmath>
#include <iostream>

int heuristic(Point a, Point b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

void PathfindingSystem::update(EntityManager& entityManager, const Map& map) {
    for (const auto& entity : entityManager.getEntities()) {
        if (entityManager.hasComponent<PathfindingComponent>(entity->getID()) &&
            entityManager.hasComponent<PositionComponent>(entity->getID())) {            
            auto pathComp = entityManager.getComponent<PathfindingComponent>(entity->getID());
            auto posComp = entityManager.getComponent<PositionComponent>(entity->getID());

            // Calcola il percorso una sola volta se è vuoto
            if (pathComp->path.empty()) {
                std::cout << "Calculating path for entity " << entity->getID() << std::endl;
                std::vector<std::vector<int>> grid = map.getGrid();
                pathComp->path = findPath(grid, {posComp->x / 40, posComp->y / 40}, {10, 10}); // fixed destination for now
            }

            // Muovi lungo il percorso
            if (!pathComp->path.empty() && pathComp->currentStep < pathComp->path.size()) {
                Point next = pathComp->path[pathComp->currentStep];
                posComp->x = next.first * 40;
                posComp->y = next.second * 40;
                pathComp->currentStep++;
            }
        }
    }
}

std::vector<std::pair<float, float>> PathfindingSystem::findPath(const std::vector<std::vector<int>>& grid, Point start, Point goal) {
    std::priority_queue<std::pair<int, Point>, std::vector<std::pair<int, Point>>, std::greater<>> openSet;
    std::map<Point, Point> cameFrom;
    std::map<Point, int> gScore;

    openSet.emplace(0, start);
    gScore[start] = 0;

    while (!openSet.empty()) {
        Point current = openSet.top().second;
        openSet.pop();

        if (current == goal) {
            std::vector<Point> path;
            while (cameFrom.find(current) != cameFrom.end()) {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (auto& dir : std::vector<Point>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
            Point neighbor = {current.first + dir.first, current.second + dir.second};
            if (neighbor.first >= 0 && neighbor.second >= 0 &&
                neighbor.first < grid[0].size() && neighbor.second < grid.size() &&
                grid[neighbor.second][neighbor.first] == 0) {

                int tentative_gScore = gScore[current] + 1;
                if (!gScore.count(neighbor) || tentative_gScore < gScore[neighbor]) {
                    cameFrom[neighbor] = current;
                    gScore[neighbor] = tentative_gScore;
                    openSet.emplace(tentative_gScore + heuristic(neighbor, goal), neighbor);
                }
            }
        }
    }
    return {};
}
