#ifndef JATEKMENET_H_INCLUDED
#define JATEKMENET_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "jatekmenet.h"

/**
 *@file jatekmenet.h
 *@brief Tartalmazza a játékmenetért felelõs függvények deklarációját és a játékban használt struktúrák zömét
 */

/**
 *@brief Egy négyzet elhelyezkedését tárolja a pályán
 *
 */
// Egy pont a palyan, ezen lehetnek novenyek, lovedekek, vagy zombik
typedef struct Pont {
    /** A négyzet oszlop és sora*/
    int x, y;
} Pont;

/**
 *@brief Egy téglalap adatait tároló struktúra
 */
typedef struct Rects {
    /** Egy téglalap x, y koordinátája szélessége és magassága*/
    int x, y, w, h;
} Rects;

/**
 *@brief Egy zombi adatait tároló struktúra
 */
typedef struct Zombi {
    /** A zombi élete*/
    int hp;
    /** A zombi elhelyezkedése a pályán (melyik négyzetbe van)*/
    Pont pozicio;
    struct Zombi* next;
    struct Zombi* prev;
}Zombi;
/**
 *@brief A zombikat tartalmazó dinamikus tömb
 */
typedef struct Zombie_list {
    /** A zombik struktúrájának tömbjére mutató pointer*/
    Zombi* first;
} Zombie_list;

/**
 *@brief Egy lovedek adatai
 */
typedef struct Lovedek {
    /**Poziciója a pályán*/
    Pont pozicio;
    struct Lovedek* next;
    struct Lovedek* prev;
} Lovedek;
/**
 *@brief A lövedékek dinamikus tömbje
 */
typedef struct Lovedek_list {
    /** A lovedékek tömbjére mutató pointer*/
    Lovedek* first;
} Lovedek_list;

/**
 *@brief Egy peashooter adatait tartalmazó struktúra
 */
typedef struct Peashooter {
    /**A peashooter élete*/
    int hp;
    /**A peashooter lövéséig hátralévõ idõ*/
    int action_time;
    /**Poziciója a pályán, hányadik oszlop, hányadik sor*/
    Pont pozicio;
    struct Peashooter* next;
    struct Peashooter* prev;
} Peashooter;
/**
 *@brief A peashootereket tartalmazó dinamikus tömb struktúrája
 */
typedef struct Peashooter_list {
    /**A peashooterek tömbjére mutató pointer*/
    Peashooter* first;
} Peashooter_list;
/**
 *@bief Egy dió/krumpli adatait tartalmazó struktúra
 */
typedef struct Wallnut {
    /** A krumpli aktuális élete*/
    int hp;
    /** A krumpli poziciója, oszlop, sor*/
    Pont pozicio;
    struct Wallnut* next;
    struct Wallnut* prev;
} Wallnut;
/**
 *@brief A krumplikat tartalmazó dinamikus tömb
 */
typedef struct Wallnut_list {
    /** A krumplikat tartalmazó tömbre mutató pointer*/
    Wallnut* first;
} Wallnut_list;
/**
 *@brief Egy napraforgó struktúrája
 */
typedef struct Sunflower {
    /** A napraforgó aktuális élete*/
    int hp;
    /** A napraforgó akciójáig mennyi idõ van*/
    int action_time;
    /** A napraforgó poziciója*/
    Pont pozicio;
    struct Sunflower* next;
    struct Sunflower* prev;
} Sunflower;
/**
 *@brief A napraforgókat tartalmazó dinamikus tömb
 */
typedef struct Sunflower_list {
    /** A napraforgók tömbjére mutató pointer*/
    Sunflower* first;
} Sunflower_list;
/**
 *@brief A különbözõ növények dinamikus tömbjeit tartalmazó struktúra
 */
typedef struct Novenyek {
    /** A peashooterek dinamikus tömbje*/
    Peashooter_list peashooters_list;
    /** A wallnutok dinamikus tömbje*/
    Wallnut_list wallnuts_list;
    /** A sunbflower-ek dinamikus tömbje*/
    Sunflower_list sunflowers_list;
} Novenyek;

/**
 *@brief Egy játékmenet minden adatát tárolja
 *
 * Ezzel az egy struktúrával leírható a játék
 */
typedef struct Jatek {
    /** A játék téglalapjai, ezen vannak a növények*/
    Rects** palya;
    /** A sorok száma*/
    int sor;
    /** Az oszlopok száma*/
    int oszlop;
    /** Az ablak magassága*/
    int h;
    /** Az ablak szélessége*/
    int w;
    /** Mennyi ideje fut a játék*/
    int time;
    /** Hany eleted maradt*/
    int elet;
    /** Az aktuális pontszámod*/
    int pont;
    /** Az aktuális napocskáidnak a száma*/
    int napocska;
    /** A növények dinamikus tömbjeit tároló struktúra*/
    Novenyek novenyek;
    /** A zombik dinamikus tömbje*/
    Zombie_list zombies_list;
    /** A lövedékek dinamikus tömbje*/
    Lovedek_list lovedekek_list;
} Jatek;

bool uj_jatek(Jatek* game, double oslop, double sor, double w, double h);
void jatek_felszabadit (Jatek* game);
void jatek_kor(Jatek* game);

#endif // JATEKMENET_H_INCLUDED
