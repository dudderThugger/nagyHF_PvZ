#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "jatekmenet.h"
#include "debugmalloc.h"
#include <time.h>
/**
 *@file zombie.h
 *@brief A zombikhoz tartoz� f�ggv�nyek deklar�l�sa
 *
 */

enum{ZOMBIE_MOVE = 3};
enum{ZOMBIE_HP = 7};
enum{ZOMBIE_SPAWN_TIME = 5};
void zombie_actions(Zombie_list* zombie_list, Novenyek* novenyek, Rects** palya, int* life);
bool van_noveny (Pont p, Novenyek* novenyek, Rects** palya, Peashooter** pea, Wallnut** wall, Sunflower** sun);
void zombie_spawner (int time, Zombie_list* zombie_list, int width);
#endif // ZOMBIE_H_INCLUDED