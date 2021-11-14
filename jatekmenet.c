#include <stdio.h>
#include <stdlib.h>
#include "jatekmenet.h"
#include "debugmalloc.h"
#include "plants.h"
#include "bullets.h"
#include "zombie.h"

/**
 *@file jatekmenet.c
 *@brief A játék állásának manipulálásához köthetõ legfontosabb függvényeket tárolja
 *
 * A játék létrehozását és mentését, a dicsõséglista irányítását, a menü irányítását,
 * a játék által használt dinamikus tömbök felszabadítását végzõ függvények mind itt találhatóak meg
 */
/**
 *@brief A játék legelején ez a függvény végzi el a játék kezdéséhez szükséges lépéseket
 *
 * Létrehozza a pálya téglalapjait tároló dinamikus tömböt és feltölti a téglalapok adataival
 * Létrehoz pointereket a dinamikus tömbökhöz, hogy késõbb könnyebben kezelhetõ legyen
 * Beállítja a kezdõértékeket (pl. idõ, pont)
 *@param game A játékot tartalmazó struktúra, amit módosítunk
 *@param oszlop Az oszlopok száma (azért valós, hogy az osztásnál elkerüljük az esetleges kerekítéseket)
 *@param sor A sorok száma
 *@param width Az ablak szélessége
 *@param height Az ablak magassága
 */
bool uj_jatek (Jatek* game, double oszlop, double sor, double width, double height) {
    bool sikeres = true;
    // Palya letrehozasa
    game -> sor = sor;
    game -> oszlop = oszlop;
    game -> w = width;
    game -> h = height;
    game -> palya = (struct Rects**) malloc(game -> sor * sizeof(struct Rects**));
    if(game -> palya == NULL)
        sikeres = false;
    for(int i = 0; i < game -> sor; ++i) {
        game -> palya[i] = (struct Rects*) malloc(game -> oszlop * sizeof(struct Rects));
        if(game -> palya[i] == NULL)
            sikeres = false;
    }
    if(game -> palya[0] != NULL){
            for(int i = 0; i < sor; ++i){
                for(int j = 0; j < oszlop; ++j) {
                    Rects akt = {.x = ((width/oszlop) * j), .y = ((height/sor) * i)+60, .w = (width/oszlop), .h = (height/sor)};
                    game -> palya[i][j] = akt;
                }
            }
    }

    game -> time = 0;
    game -> pont = 0;
    // Letrehozunk egy cimet a dinamikus tomboknek (a kesobbi fuggvenyekben majd az atmeretezesnel felszabaditjuk es ujracsinaljuk)
    game -> zombik_din.zombik = (struct Zombi*) malloc (sizeof(struct Zombi));
    if(game -> zombik_din.zombik == NULL)
        sikeres = false;
    game -> zombik_din.meret = 0;
    game -> lovedekek_din.lovedekek = (struct Lovedek*) malloc (sizeof(struct Lovedek));
    if(game -> lovedekek_din.lovedekek == NULL)
        sikeres = false;
    game -> lovedekek_din.meret = 0;
    game -> time = 0;
    game -> pont = 0;
    game -> napocska = 50;
    game -> novenyek.peashooters_din.peashooters = (struct Peashooter*) malloc(sizeof(struct Peashooter));
    if(game -> novenyek.peashooters_din.peashooters  == NULL)
        sikeres = false;
    game -> novenyek.peashooters_din.meret = 0;
    game -> novenyek.wallnuts_din.wallnuts = (struct Wallnut*) malloc(sizeof(struct Wallnut));
    if(game -> novenyek.wallnuts_din.wallnuts == NULL)
        sikeres = false;
    game -> novenyek.wallnuts_din.meret = 0;
    game -> novenyek.sunflowers_din.sunflowers = (struct Sunflower*) malloc (sizeof(struct Sunflower));
    if(game -> novenyek.sunflowers_din.sunflowers == NULL)
        sikeres = false;
    game -> novenyek.sunflowers_din.meret = 0;
    return sikeres;
}
/**
 *@brief A játék által használt dinamikus tömbök felszabadítása
 *@param game A játékot tároló struktúra
 */
// Felszabaditja a lefoglalt memoriateruletet
void jatek_felszabadit (Jatek* game) {
    for(int i = 0; i < game -> sor; ++i) {
       free(game-> palya[i]);
    }
    free(game->palya);
    free(game -> zombik_din.zombik);
    free(game -> lovedekek_din.lovedekek);
    free(game -> novenyek.peashooters_din.peashooters);
    free(game -> novenyek.wallnuts_din.wallnuts);
    free(game -> novenyek.sunflowers_din.sunflowers);
}

/**
 *@brief A játék egy körét elvégzõ függvény
 *@param game A játék struktúrája
 */
void jatek_kor(Jatek* game) {
    noveny_akciok(&(game -> novenyek), &(game -> lovedekek_din), &(game -> napocska));
    lovedek_mozog(&(game -> lovedekek_din), &(game-> zombik_din), game -> sor);
    zombi_akciok(&(game -> zombik_din), &(game->novenyek), &(game->elet), game->w, game->oszlop);
}
