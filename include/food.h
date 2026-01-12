#pragma once
#include "game.h"
#include <SDL3/SDL_rect.h>

extern color foodColor;

void initFood();
point randomFood();
void DrawFood();
