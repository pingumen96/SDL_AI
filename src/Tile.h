#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

class Tile {
public:
    Tile(int x, int y, int size, bool isObstacle);
    void render(SDL_Renderer* renderer);

private:
    SDL_Rect rect;
    SDL_Color color;
};

#endif
