#include "MovementSystem.h"
#include <cmath>

#include <cmath>

void MovementSystem::update(EntityManager& manager, const Map& map) {
    for (const auto& entity : manager.getEntities()) {
        if (manager.hasComponent<PositionComponent>(entity->getID()) &&
            manager.hasComponent<VelocityComponent>(entity->getID())) {

            auto pos = manager.getComponent<PositionComponent>(entity->getID());
            auto vel = manager.getComponent<VelocityComponent>(entity->getID());

            float newX = pos->x + vel->dx;
            float newY = pos->y + vel->dy;

            std::cout << "New position: " << newX << ", " << newY << std::endl;
            std::cout << "Velocity: " << vel->dx << ", " << vel->dy << std::endl;

            // Verifica della traiettoria
            if (!isPathColliding(pos->x, pos->y, newX, newY, map)) {
                pos->x = newX;
                pos->y = newY;
            } else {
                // Ferma il movimento se collide
                vel->dx = 0;
                vel->dy = 0;
            }
        }
    }
}

bool MovementSystem::isColliding(float x, float y, const Map& map) {
    const int characterSize = 10; // Dimensioni del personaggio
    const int tileSize = map.getTileSize();

    // Verifica i quattro angoli del bounding box
    for (int offsetX : {0, characterSize}) {
        for (int offsetY : {0, characterSize}) {
            float checkX = x + offsetX;
            float checkY = y + offsetY;

            int tileX = static_cast<int>(checkX) / tileSize;
            int tileY = static_cast<int>(checkY) / tileSize;

            if (map.isCollidingWithWall(tileX * tileSize, tileY * tileSize)) {
                std::cout << "Collision detected at: " << tileX << ", " << tileY << std::endl;
                return true;
            }
        }
    }

    return false;
}


bool MovementSystem::isPathColliding(float startX, float startY, float endX, float endY, const Map& map) {
    float dx = endX - startX;
    float dy = endY - startY;

    // Calcola il numero di passi, assicurandoti che sia almeno 1
    int steps = std::max(1, static_cast<int>(std::max(std::abs(dx), std::abs(dy)) / map.getTileSize()));

    float stepX = dx / steps;
    float stepY = dy / steps;

    for (int i = 0; i <= steps; ++i) {
        float currentX = startX + i * stepX;
        float currentY = startY + i * stepY;

        if (map.isCollidingWithWall(currentX, currentY)) {
            return true; // Collisione trovata lungo la traiettoria
        }
    }

    return false; // Nessuna collisione
}



void MovementSystem::seek(EntityManager& manager, int entityID, float targetX, float targetY, float speed) {
    auto pos = manager.getComponent<PositionComponent>(entityID);
    auto vel = manager.getComponent<VelocityComponent>(entityID);

    float dx = targetX - pos->x;
    float dy = targetY - pos->y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance > 0) {
        vel->dx = (dx / distance) * speed;
        vel->dy = (dy / distance) * speed;
    }
}

void MovementSystem::flee(EntityManager& manager, int entityID, float dangerX, float dangerY, float speed) {
    auto pos = manager.getComponent<PositionComponent>(entityID);
    auto vel = manager.getComponent<VelocityComponent>(entityID);

    float dx = pos->x - dangerX;
    float dy = pos->y - dangerY;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance > 0) {
        vel->dx = (dx / distance) * speed;
        vel->dy = (dy / distance) * speed;
    }
}
