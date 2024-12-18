#ifndef PATHFINDINGSYSTEM_H
#define PATHFINDINGSYSTEM_H

#include "ECS.h"
#include "Components.h"
#include "Map.h"
#include <vector>

class PathfindingSystem {
public:
    void update(EntityManager& entityManager, const Map& map);

private:
    std::vector<std::pair<int, int>> findPath(const std::vector<std::vector<int>>& grid, Point start, Point goal);
};

#endif