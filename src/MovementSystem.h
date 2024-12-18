#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "ECS.h"
#include "Components.h"
#include "Map.h"
#include <cmath>

class MovementSystem {
public:
    void update(EntityManager& manager, const Map& map);

    void seek(EntityManager& manager, int entityID, float targetX, float targetY, float speed);
    void flee(EntityManager& manager, int entityID, float dangerX, float dangerY, float speed);

private:
    bool isColliding(float x, float y, const Map& map);
    bool isPathColliding(float startX, float startY, float endX, float endY, const Map& map);
};

#endif
