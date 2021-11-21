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
    game -> zombies_list.first = NULL;
    game -> zombies_list.meret = 0;
    game -> lovedekek_list.first = NULL;
    game -> lovedekek_list.meret = 0;
    game -> time = 0;
    game -> pont = 0;
    game -> napocska = 50;
    game->novenyek.peashooters_list.first = NULL;
    game->novenyek.peashooters_list.meret = 0;    
    game->novenyek.wallnuts_list.first = NULL;
    game->novenyek.wallnuts_list.meret = 0;
    game->novenyek.sunflowers_list.first = NULL;
    game->novenyek.sunflowers_list.meret = 0;
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
    if(game->zombies_list.meret != 0){
        Zombi* iter = game->zombies_list.first;
        Zombi* next;
        while(iter->next != NULL){
            next = iter->next;
            free(iter);
            iter = next;
        }
    }
    if(game->novenyek.peashooters_list.meret != 0){
        Peashooter* iter = game->novenyek.peashooters_list.first;
        Peashooter* next;
        while(iter->next != NULL){
            next = iter->next;
            free(iter);
            iter = next;
        }
    }
    if(game->novenyek.sunflowers_list.meret != 0){
        Sunflower* iter = game->novenyek.sunflowers_list.first;
        Sunflower* next;
        while(iter->next != NULL){
            next = iter->next;
            free(iter);
            iter = next;
        }
    }
    if(game->novenyek.wallnuts_list.meret != 0){
        Wallnut* iter = game->novenyek.wallnuts_list.first;
        Wallnut* next;
        while(iter->next != NULL){
            next = iter->next;
            free(iter);
            iter = next;
        }
    }
}

/**
 *@brief A játék egy körét elvégzõ függvény
 * Először elvégzi a növények akcióját (lövés, napocska termelés), aztán a lövedékek mozgatását,
 * és legvégül a zombik akcióját (ha beérnek a zombik leszedjük őket, megölik a növényeket... stb)
 *@param game A játék struktúrája
 */
void jatek_kor(Jatek* game) {
    plant_actions(&game->novenyek, &game->lovedekek_list,game->w,game->sor,&game->napocska);
    zombie_actions(&game->zombies_list,&game->novenyek,game->palya, &game->elet);
    lovedek_mozog(&game->lovedekek_list, &game->zombies_list,game->sor);
    if(game->time % 5 == 0) {
        game->napocska += 25;
    }
}
