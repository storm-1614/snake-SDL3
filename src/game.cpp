#include "../include/game.h"
#include "../include/win.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

const int h = 20;
const int w = 20;

void drawRect(int x, int y,color c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    point dot{x, y};
    SDL_FRect rect{(float)dot.x, (float)dot.y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

void drawPic(SDL_Texture *texture, SDL_FRect rect)
{
    SDL_Vertex verts[4] = {{{rect.x, rect.y}, {255, 255, 255, 255}, {0.0f, 0.0f}},
                           {{rect.x + rect.w, rect.y}, {255, 255, 255, 255}, {1.0f, 0.0f}},
                           {{rect.x + rect.w, rect.y + rect.h}, {255, 255, 255, 255}, {1.0f, 1.0f}},
                           {{rect.x, rect.y + rect.h}, {255, 255, 255, 255}, {0.0f, 1.0f}}};
    int indices[6] = { 0, 1, 2, 2, 3, 0 };
    SDL_RenderGeometry(renderer, texture, verts, 4, indices, 6);

}
