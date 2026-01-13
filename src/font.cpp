#include "../include/win.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_textengine.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdlib>
#include <cstring>

TTF_Font *font = NULL;
SDL_Color white = {255, 255, 255};
SDL_FRect fontRect;
SDL_Surface *fontSurface = NULL;
SDL_Texture *fontTexture = NULL;

/*
 * 初始化字体
 * 初始化模块
 * 加载字体文件
 */
void initFont()
{
    if (!TTF_Init())
    {
        SDL_Log("错误：字体模块加载失败");
        exit(1);
    }

    if ((font = TTF_OpenFont("sources/SourceHanSansCN-Normal.otf", 20)) == NULL)
    {
        SDL_Log("字体文件加载失败");
        exit(2);
    }
}

/*
 * 渲染字体
 * 输入颜色和文字即可
 */
void loadFont(SDL_Color c, const char *text)
{
    size_t length = strlen(text);
    fontRect = SDL_FRect{0, 0, (float)length * 10, 40};

    if (fontTexture)
    {
        SDL_DestroyTexture(fontTexture);
        fontTexture = NULL;
    }
    if ((fontSurface = TTF_RenderText_Blended(font, text, length, c)) == NULL)
    {
        SDL_Log("字体表面加载失败");
        exit(2);
    }
    if ((fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface)) == NULL)
    {
        SDL_Log("字体纹理加载失败");
        exit(2);
    }
    SDL_DestroySurface(fontSurface);
    fontSurface = NULL;
}

/*
 * 绘制字体
 */
void drawFont()
{
    if (!SDL_RenderTexture(renderer, fontTexture, &fontRect, &fontRect))
    {
        SDL_Log("字体渲染失败");
        exit(2);
    }
}

void destoryFont()
{
    SDL_DestroyTexture(fontTexture);
    fontTexture = NULL;
}
