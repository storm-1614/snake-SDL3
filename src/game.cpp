#include "../include/game.h"
#include "../include/win.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

const int h = 20;
const int w = 20;


void test()
{
    SDL_Log("This is a test\n");
}

void drawRect(int x, int y,color c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
    SDL_Point dot{x, y};
    SDL_FRect rect{(float)dot.x, (float)dot.y, w, h};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}
