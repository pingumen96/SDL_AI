#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "ECS.h"
#include "Components.h"

class MovementSystem {
public:
    void update(EntityManager& manager) {
        for (const auto& entity : manager.getEntities()) {
            if (manager.hasComponent<PositionComponent>(entity->getID()) &&
                manager.hasComponent<VelocityComponent>(entity->getID())) {
                
                auto pos = manager.getComponent<PositionComponent>(entity->getID());
                auto vel = manager.getComponent<VelocityComponent>(entity->getID());

                pos->x += vel->dx;
                pos->y += vel->dy;
            }
        }
    }
};

#endif
