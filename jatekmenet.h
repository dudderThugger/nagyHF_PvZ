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
}Zombi;

/**
 *@brief A zombikat tartalmazó dinamikus tömb
 */
typedef struct Zombi_din {
    /** A zombik struktúrájának tömbjére mutató pointer*/
    Zombi* zombik;
    /** A mérete a tömbnek*/
    int meret;
} Zombi_din;

/**
 *@brief Egy lovedek adatai
 */
typedef struct Lovedek {
    /**Poziciója a pályán*/
    Pont pozicio;
} Lovedek;
/**
 *@brief A lövedékek dinamikus tömbje
 */
typedef struct Lovedek_din {
    /** A lovedékek tömbjére mutató pointer*/
    Lovedek* lovedekek;
    /**A dinamikus tömb mérete*/
    int meret;
} Lovedek_din;

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
} Peashooter;
/**
 *@brief A peashootereket tartalmazó dinamikus tömb struktúrája
 */
typedef struct Peashooter_din {
    /**A peashooterek tömbjére mutató pointer*/
    Peashooter* peashooters;
    /**A tömb mérete*/
    int meret;
} Peashooter_din;
/**
 *@bief Egy dió/krumpli adatait tartalmazó struktúra
 */
typedef struct Wallnut {
    /** A krumpli aktuális élete*/
    int hp;
    /** A krumpli poziciója, oszlop, sor*/
    Pont pozicio;
} Wallnut;
/**
 *@brief A krumplikat tartalmazó dinamikus tömb
 */
typedef struct Wallnut_din {
    /** A krumplikat tartalmazó tömbre mutató pointer*/
    Wallnut* wallnuts;
    /** A tömb mérete*/
    int meret;
} Wallnut_din;
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
} Sunflower;
/**
 *@brief A napraforgókat tartalmazó dinamikus tömb
 */
typedef struct Sunflower_din {
    /** A napraforgók tömbjére mutató pointer*/
    Sunflower* sunflowers;
    /**A tömb mérete*/
    int meret;
} Sunflower_din;
/**
 *@brief A különbözõ növények dinamikus tömbjeit tartalmazó struktúra
 */
typedef struct Novenyek {
    /** A peashooterek dinamikus tömbje*/
    Peashooter_din peashooters_din;
    /** A wallnutok dinamikus tömbje*/
    Wallnut_din wallnuts_din;
    /** A sunbflower-ek dinamikus tömbje*/
    Sunflower_din sunflowers_din;
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
    Zombi_din zombik_din;
    /** A lövedékek dinamikus tömbje*/
    Lovedek_din lovedekek_din;
} Jatek;

bool uj_jatek(Jatek* game, double sor, double oszlop, double w, double h);
void jatek_felszabadit (Jatek* game);
void jatek_kor(Jatek* game);

#endif // JATEKMENET_H_INCLUDED
