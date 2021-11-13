#ifndef MEGJELENIT_H_INCLUDED
#define MEGJELENIT_H_INCLUDED
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <SDL_image.h>
#include "jatekmenet.h"
#include "debugmalloc.h"

typedef enum SelectedItem {
    PEASHOOTER,
    SUNFLOWER,
    WALLNUT,
    NOTHING
} SelectedItem;

void draw_background(SDL_Renderer *renderer, Rects** palya, int const sor, int const oszlop);

#endif // MEGJELENIT_H_INCLUDED
