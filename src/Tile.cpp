#include "Tile.h"

Tile::Tile(int x, int y, int size, bool isObstacle) {
    rect = {x, y, size, size};
    color = isObstacle ? SDL_Color{255, 0, 0, 255} : SDL_Color{200, 200, 200, 255}; // Rosso per ostacoli
}

void Tile::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);

    // Bordo nero per ogni tile
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
}
