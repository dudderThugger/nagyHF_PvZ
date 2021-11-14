#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "jatekmenet.h"
#include "debugmalloc.h"
/**
 *@file zombie.h
 *@brief A zombikhoz tartozó függvények deklarálása
 *
 */

enum{ZOMBIE_MOVE =3 };
enum{ZOMBIE_HP = 7};
void zombi_akciok(Zombi_din* zombik_din, Novenyek* novenyek, int* elet, int szeles, int oszlop);
void zombi_torol(int hanyadik, Zombi_din* zombi_din);
void spawn_zombie(Pont hova, Zombi_din* zombies_din);
#endif // ZOMBIE_H_INCLUDED
