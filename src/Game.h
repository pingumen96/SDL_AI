#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <memory>           
#include "ECS.h"      
#include "Map.h"         
#include "PathfindingSystem.h" 

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
    EntityManager entityManager;                    // Gestore delle entità
    std::shared_ptr<Map> map;                      // Mappa condivisa
    std::shared_ptr<Entity> seeker;                // Seeker gestito come shared_ptr
    std::shared_ptr<Entity> target;                // Target gestito come shared_ptr
    PathfindingSystem pathfindingSystem;           // Sistema di pathfinding

    // Timing per l'aggiornamento
    const int UPDATE_DELAY = 200;
    Uint32 lastUpdateTime = 0;
};

#endif
