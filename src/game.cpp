#include "../include/game.h"
#include "../include/win.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

const int h = 20;
const int w = 20;

void drawRect(int x, int y,color c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_Point dot{x, y};
    SDL_FRect rect{(float)dot.x, (float)dot.y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}
