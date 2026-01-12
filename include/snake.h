#pragma once
#include "game.h"
#include <list>
#include <SDL3/SDL_rect.h>

extern std::list<point> snakeBody;
extern color snakeColor;

void initSnake();
void drawSnake();

