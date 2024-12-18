#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ECS.h"
#include <SDL2/SDL.h>

struct PositionComponent : public Component {
    int x, y;
    PositionComponent(int x, int y) : x(x), y(y) {}
};

struct VelocityComponent : public Component {
    int dx, dy;
    VelocityComponent(int dx, int dy) : dx(dx), dy(dy) {}
};

// AI components
using Point = std::pair<int, int>;

struct PathfindingComponent : public Component {
    std::vector<Point> path;
    int currentStep;
    PathfindingComponent() : currentStep(0) {}
};

struct SteeringComponent : public Component {
    Point targetPosition;
    float speed;
    SteeringComponent(Point target, float spd) : targetPosition(target), speed(spd) {}
};

struct StateMachineComponent : public Component {
    enum State { IDLE, PATROLLING, CHASING, ATTACKING };
    State currentState;
    StateMachineComponent() : currentState(IDLE) {}
};

#endif
