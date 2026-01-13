#pragma once
#include <SDL3_ttf/SDL_ttf.h>

extern TTF_Font *font;
extern SDL_Color white;


void initFont();
void loadFont(SDL_Color c, const char *text);
void drawFont();
void destoryFont();
