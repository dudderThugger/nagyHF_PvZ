#ifndef PLANTS_H_INCLUDED
#define PLANTS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "jatekmenet.h"
#include "debugmalloc.h"

/**
 *@file plants.h
 *@brief A növényekhez kapcsolódó függvények deklarációja
 */
void noveny_akciok(Novenyek* novenyek, Lovedek_din* lovedekek, int* napocska);
void peashooter_torol(int hanyadik, Peashooter_din* peashooter_din);
void wallnut_torol(int hanyadik, Wallnut_din* wallnut_din);
void sunflower_torol(int hanyadik, Sunflower_din* sunflower_din);
void spawn_peashooter(Pont poz, Peashooter_din* peashooters);
void spawn_sunflower(Pont poz, Sunflower_din* sunflowers);
void spawn_wallnut(Pont poz, Wallnut_din* wallnuts);

#endif // PLANTS_H_INCLUDED
