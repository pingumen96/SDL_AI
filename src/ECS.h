#ifndef ECS_H
#define ECS_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <typeindex>
#include <iostream>

// Base Component
class Component {
public:
    virtual ~Component() = default;
};

// Entity
class Entity {
public:
    Entity(int id) : id(id) {}
    int getID() const { return id; }
private:
    int id;
};

// EntityManager
class EntityManager {
public:
    EntityManager() : nextEntityID(0) {}

    std::shared_ptr<Entity> createEntity() {
        auto entity = std::make_shared<Entity>(nextEntityID++);
        entities.push_back(entity);
        std::cout << "Created entity with ID " << entity->getID() << std::endl;
        return entity;
    }

    template <typename T>
    void addComponent(int entityID, std::shared_ptr<T> component) {
        components[std::type_index(typeid(T))][entityID] = component;
        std::cout << "Added component of type " << typeid(T).name() << " to entity " << entityID << std::endl;
    }

    template <typename T>
    std::shared_ptr<T> getComponent(int entityID) {
        return std::static_pointer_cast<T>(components[std::type_index(typeid(T))][entityID]);
    }

    template <typename T>
    bool hasComponent(int entityID) {
        return components[std::type_index(typeid(T))].find(entityID) != components[std::type_index(typeid(T))].end();
    }

    const std::vector<std::shared_ptr<Entity>>& getEntities() const { return entities; }

private:
    int nextEntityID;
    std::vector<std::shared_ptr<Entity>> entities; // Vettore di shared_ptr per gestire le entità
    std::unordered_map<std::type_index, std::unordered_map<int, std::shared_ptr<Component>>> components;
};

#endif
