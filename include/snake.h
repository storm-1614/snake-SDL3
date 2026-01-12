#pragma once
#include "game.h"
#include <SDL3/SDL_rect.h>
#include <deque>

extern std::deque<point> snakeBody;
extern color snakeColor;
enum direction
{
    left,
    right,
    up,
    down
};

extern direction snakeDire;

void initSnake();
void drawSnake();
void updateSnake();
