#ifndef PATHFINDINGSYSTEM_H
#define PATHFINDINGSYSTEM_H

#include "ECS.h"
#include "Components.h"
#include "Map.h"
#include <vector>

class PathfindingSystem {
public:
    void update(EntityManager& entityManager, const Map& map);
    std::pair<float, float> getNextPathPoint(const EntityManager& entityManager, int entityID);

private:
    std::vector<std::pair<float, float>> findPath(const std::vector<std::vector<int>>& grid, Point start, Point goal);
};

#endif
