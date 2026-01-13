#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>

extern SDL_Surface *bgSurface;
extern SDL_Texture *bgTexture;

extern int score;

// 包含 RGBA 的颜色结构体
struct color
{
    int r, g, b, a;
};

/*
* 坐标结构体
* 重载 == 运算符，std::find 需要用
*/
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
void drawPic(SDL_Texture *texture, SDL_FRect rect);
bool eventHandle();
void redraw();
void quit();
