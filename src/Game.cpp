#include "Game.h"

Game::Game() {}
Game::~Game() {}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (window && renderer) {
            isRunning = true;

            // Inizializza la mappa come shared_ptr
            map = std::make_shared<Map>(15, 20, 40, 0.2f);

            // Crea le entità come shared_ptr
            seeker = entityManager.createEntity();
            target = entityManager.createEntity();

            // Configura i componenti
            entityManager.addComponent(seeker->getID(), std::make_shared<PositionComponent>(0, 0));
            entityManager.addComponent(seeker->getID(), std::make_shared<PathfindingComponent>());
            entityManager.addComponent(target->getID(), std::make_shared<PositionComponent>(10 * 40, 10 * 40));
        }
    } else {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        isRunning = false;
    }
    return isRunning;
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        isRunning = false;
    }
}

void Game::update() {
    Uint32 currentTime = SDL_GetTicks();

    if (currentTime > lastUpdateTime + UPDATE_DELAY) {
        // Aggiorna il sistema di pathfinding
        pathfindingSystem.update(entityManager, *map);

        lastUpdateTime = currentTime;
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Renderizza la mappa
    map->render(renderer);

    // Renderizza il seeker
    auto seekerPos = entityManager.getComponent<PositionComponent>(seeker->getID());
    SDL_Rect seekerRect = {seekerPos->x, seekerPos->y, 40, 40};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &seekerRect);

    // Renderizza il target
    auto targetPos = entityManager.getComponent<PositionComponent>(target->getID());
    SDL_Rect targetRect = {targetPos->x, targetPos->y, 40, 40};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &targetRect);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    map.reset();
    seeker.reset();
    target.reset();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!\n";
}
