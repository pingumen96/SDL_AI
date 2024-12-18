#include "Game.h"

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr) {}
Game::~Game() {}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (!window) {
            std::cerr << "Failed to create SDL Window: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (!renderer) {
            std::cerr << "Failed to create SDL Renderer: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        isRunning = true;

        // Inizializza la mappa come shared_ptr
        map = std::make_shared<Map>(15, 20, 40, 0.2f);

        // Crea le entità come shared_ptr
        seeker = entityManager.createEntity();
        target = entityManager.createEntity();

        // Configura i componenti
        entityManager.addComponent(seeker->getID(), std::make_shared<PositionComponent>(0, 0));
        entityManager.addComponent(seeker->getID(), std::make_shared<VelocityComponent>(0, 0, true));

        auto randomPosition = map->getRandomValidPosition();

        entityManager.addComponent(target->getID(), std::make_shared<PositionComponent>(randomPosition.first, randomPosition.second));
    } else {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
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
        auto targetPosition = entityManager.getComponent<PositionComponent>(target->getID());

        if (targetPosition) {
            movementSystem.seek(entityManager, seeker->getID(), targetPosition->x, targetPosition->y, 2.0f);
        }
        // Aggiorna il movimento delle entità
        movementSystem.update(entityManager, *map);

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
    if (seekerPos) {
        SDL_Rect seekerRect = {static_cast<int>(seekerPos->x), static_cast<int>(seekerPos->y), 10, 10};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &seekerRect);
    }

    // Renderizza il target
    auto targetPos = entityManager.getComponent<PositionComponent>(target->getID());
    if (targetPos) {
        SDL_Rect targetRect = {static_cast<int>(targetPos->x), static_cast<int>(targetPos->y), 10, 10};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &targetRect);
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    map.reset();
    seeker.reset();
    target.reset();

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);

    SDL_Quit();
    std::cout << "Game cleaned!\n";
}
