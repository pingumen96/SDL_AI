#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <memory>           
#include "ECS.h"      
#include "Map.h"         
#include "PathfindingSystem.h" 
#include "MovementSystem.h"

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Game systems and entities
    EntityManager entityManager;
    std::shared_ptr<Map> map;
    std::shared_ptr<Entity> seeker;
    std::shared_ptr<Entity> target;    

    // Game systems      
    PathfindingSystem pathfindingSystem;
    MovementSystem movementSystem;
    
    // Timing per l'aggiornamento
    const int UPDATE_DELAY = 10;
    Uint32 lastUpdateTime = 0;
};

#endif
