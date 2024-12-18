#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ECS.h"
#include <SDL2/SDL.h>

struct PositionComponent : public Component {
    float x, y;
    PositionComponent(float x, float y) : x(x), y(y) {}
};

struct VelocityComponent : public Component {
    float dx, dy;
    bool dynamic = false;

    VelocityComponent(float dx, float dy, bool dynamic = false) : dx(dx), dy(dy), dynamic(dynamic) {}
};

// AI components
using Point = std::pair<float, float>;

struct PathfindingComponent : public Component {
    std::vector<Point> path;
    int currentStep = 0;
    int targetID = -1;
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
