#include <stdio.h>
#include <stdlib.h>
#include "jatekmenet.h"
#include "debugmalloc.h"
#include "plants.h"
#include "bullets.h"
#include "zombie.h"
/**
 *@file bullets.c
 *@brief A lövedékekhez kapcsolódó függvények definiciója
 *
 * A lövedékek mozgatásáért, idézéséért és törléséért felelõs függvények
 */

 /**
  *@brief Egy lövedék idézése
  *@param poz A pont (téglalap helyzete) ahol a lövedék teremtõdni fog
  *@param lovedekek_din A lövedékeket tartalmazó dinamikus tömb
  */
void spawn_lovedek(Pont poz, Lovedek_din* lovedekek_din){
    Lovedek* uj = (struct Lovedek*) malloc ((lovedekek_din -> meret+1) * sizeof(struct Lovedek));
    Lovedek ujLov = {poz};
    for(int i = 0; i < lovedekek_din -> meret; ++i) {
        uj[i] = lovedekek_din -> lovedekek[i];
    }
    uj[lovedekek_din -> meret + 1] = ujLov;
    free(lovedekek_din -> lovedekek);
    lovedekek_din -> lovedekek = uj;
}
 /**
  *@brief Egy lövedék törlése
  *@param hanyadik Hanyadik lövedéket kell törölni a dinamikus tömbbõl
  *@param lovedekek_din A lövedékeket tartalmazó dinamikus tömb
  */
void lovedek_torol(int hanyadik, Lovedek_din* lovedekek_din) {
    Lovedek* uj = (struct Lovedek*) malloc ((lovedekek_din -> meret-1) * sizeof(struct Lovedek));
    int ujIndx = 0;
    for(int i = 0; i < lovedekek_din -> meret; ++i) {
        if(i != hanyadik) {
          uj[ujIndx++] = lovedekek_din -> lovedekek[i];
          ++ujIndx;
        }
    }
    lovedekek_din -> meret = ujIndx;
    free(lovedekek_din -> lovedekek);
    lovedekek_din -> lovedekek = uj;
}

/**
  *@brief Az összes lövedék mozgatása
  *@param lovedekek_din A lövedékeket tartalmazó dinamikus tömb
  *@param zombik_din A zombikat tartalmazó dinamikus tömb
  *@param oszlop A pálya szelessege, ha ezen túl megy törölni kell
  */
void lovedek_mozog(Lovedek_din* lovedekek_din, Zombi_din* zombik_din, int szeles){
    for(int i = 0; i < lovedekek_din -> meret; ++i){
        Pont aktualis = lovedekek_din -> lovedekek[i].pozicio;
        // Ha kier a lovedek toroljuk
        if(aktualis.x+1 > szeles) {
            lovedek_torol(i, lovedekek_din);
        }
        // Ha zombit talal toroljuk es sebezzuk a zombit
        for(int j = 0; j < zombik_din -> meret; ++j) {
            if(zombik_din -> zombik[j].pozicio.x == aktualis.x) {
                if(zombik_din -> zombik[j].pozicio.y == aktualis.y){
                    if(zombik_din -> zombik[j].hp == 1)
                        zombi_torol(j, zombik_din);
                    else{
                        zombik_din -> zombik[j].hp--;
                    }
                   lovedek_torol(i,lovedekek_din);
                }
            }
        }
        // Egyebkent leptetjuk a lovedeket
        ++lovedekek_din -> lovedekek[i].pozicio.x;
    }
}
