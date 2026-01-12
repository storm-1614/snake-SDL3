#pragma once
#include "game.h"
#include <SDL3/SDL_rect.h>

extern point foodPos;

void initFood();
point randomFood();
void drawFood();
void destoryFood();
