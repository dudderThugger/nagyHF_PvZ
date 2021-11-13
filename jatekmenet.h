#ifndef JATEKMENET_H_INCLUDED
#define JATEKMENET_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debugmalloc.h"

// Egy pont a palyan, ezen lehetnek novenyek, lovedekek, vagy zombik
typedef struct Pont {
    int x, y;
} Pont;

typedef struct Rects {
    int x, y, w, h;
} Rects;

typedef struct Zombi {
    int hp;
    int state; // Hany kor ota tartozkodik az aktualis mezon (egy zombi tobb korig fog egy mezon lenni leptetes elott)
    Pont pozicio;
}Zombi;
typedef struct Zombi_din {
    Zombi* zombik;
    int meret;
} Zombi_din;

typedef struct Lovedek {
    Pont pozicio;
} Lovedek;
typedef struct Lovedek_din {
    Lovedek* lovedekek;
    int meret;
} Lovedek_din;

typedef struct Peashooter {
    int hp;
    int cost;
    int action_time;
    Pont pozicio;
} Peashooter;
typedef struct Peashooter_din {
    Peashooter* peashooters;
    int meret;
} Peashooter_din;

typedef struct Wallnut {
    int hp;
    int cost;
    Pont pozicio;
} Wallnut;
typedef struct Wallnut_din {
    Wallnut* wallnuts;
    int meret;
} Wallnut_din;

typedef struct Sunflower {
    int hp;
    int cost;
    int action_time;
    Pont pozicio;
} Sunflower;
typedef struct Sunflower_din {
    Sunflower* sunflowers;
    int meret;
} Sunflower_din;

// Novenyek dinamikus tombje
typedef struct Novenyek {
    Peashooter_din peashooters_din;
    Wallnut_din wallnuts_din;
    Sunflower_din sunflowers_din;
} Novenyek;

// A jatek
typedef struct Jatek {
    Rects** palya;
    int sor;
    int oszlop;
    int h;
    int w;
    int time;
    int pont;
    int napocska;
    Novenyek novenyek;
    Zombi_din zombik_din;
    Lovedek_din lovedekek_din;
} Jatek;

bool uj_jatek(Jatek* game, double sor, double oszlop, double w, double h);
void jatek_felszabadit (Jatek* game);

#endif // JATEKMENET_H_INCLUDED
