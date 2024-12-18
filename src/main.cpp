#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
    game = new Game();

    // Inizializzazione della finestra
    if (!game->init("AI Demo in C++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false)) {
        return -1;
    }

    // Loop principale
    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    // Cleanup
    game->clean();
    return 0;
}
