#pragma once

#include <SDL3/SDL.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern const int WINDOW_HEIGHT;
extern const int WINDOW_WIDTH;

void initWin();
void runWin();
