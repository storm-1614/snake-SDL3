#pragma once
#include "game.h"
#include <SDL3/SDL_rect.h>
#include <list>

extern std::list<point> snakeBody;
extern color snakeColor;
enum direction
{
    left,
    right,
    up,
    down
};


void initSnake();
void drawSnake();
void updateSnake();
