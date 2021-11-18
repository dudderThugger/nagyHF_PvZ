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
/**
 *@file megjelenit.h
 *@brief Az egész játék megjelenítését végzõ függvények deklarációját tartalmazó fájl
 */

/**
 *@brief A kijelölhetõ elemeket tartalmazza
 */
typedef enum SelectedItem {
    PEASHOOTER,
    SUNFLOWER,
    WALLNUT,
    NOTHING
} SelectedItem;

void draw_background(SDL_Renderer *renderer, Rects** palya, int const sor, int const oszlop);
void draw_peashooters(SDL_Renderer * renderer, Rects** palya, Peashooter_din* peashooter_din);
SDL_Rect get_rect(Rects** palya, int sor, int oszlop, Pont* selected);
void draw_selectedItem(SDL_Renderer* renderer, SDL_Rect rect, SelectedItem selectedItem);
void draw_wallnuts(SDL_Renderer * renderer, Rects** palya, Wallnut_din* wallnuts_din);
void draw_sunflowers(SDL_Renderer * renderer, Rects** palya, Sunflower_din* sunflower_din);
void draw_zombies(SDL_Renderer* renderer, Rects** palya, Zombi_din* zombies_din);
void draw_bullets(SDL_Renderer* renderer, Lovedek_din* lovedekek_din, int magas);

#endif // MEGJELENIT_H_INCLUDED
