#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>

struct color
{
    int r, g, b, a;
};

struct point
{
    int x;
    int y;
    bool operator==(const point &other)
    {
        return x == other.x && y == other.y;
    }
};

void test();
void drawRect(int x, int y, color c);
