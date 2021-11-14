#include <stdio.h>
#include <stdlib.h>
#include "jatekmenet.h"
#include "debugmalloc.h"
#include "plants.h"
#include "bullets.h"
#include "zombie.h"

/**
 *@file zombie.c
 *@brief A zombikhoz tartoz� f�ggv�nyek
 *
 * A zombik akci�j��rt, mozgat�suk�rt �s id�z�s�k�rt felel�s f�ggv�nyek tal�lhat�ak itt
 */

/**
 *@brief A zombik akci�j�t ir�ny�t� f�ggv�ny
 *
 * Megn�zi hogy n�v�nyn�l, van-e ha igen akkor sebzi a n�v�nyt, ha a n�v�nynek elfogy az �lette meg is �li, ha nincs n�v�nyn�l l�p
 *
 *@param zombik_din a zombikat t�rol� dinamikus t�mb
 *@param novenyek a n�v�nyeket t�rol� strukt�ra, ami tartalmazza a dinamikus t�mb�ket
 *@param elet H�ny �let�nk maradt m�g a j�t�kban
 *@param szeles Milyen sz�les az ablakunk
 *@param oszlop H�ny oszlopos a p�ly�nk
 */
void zombi_akciok(Zombi_din* zombik_din, Novenyek* novenyek, int* elet, int szeles, int oszlop){
    for(int i = 0; i <  zombik_din -> meret; ++i) {
        Zombi aktualis = zombik_din -> zombik[i];
        // Zombi beer
        if(aktualis.pozicio.x == 0){
            zombi_torol(i, zombik_din);
            (*elet)--;
        }
        // Zombi novenynel van
        for(int j = 0; j < novenyek->peashooters_din.meret; ++i) {
            Peashooter peashooter = novenyek -> peashooters_din.peashooters[i];
            if(aktualis.pozicio.y == peashooter.pozicio.y){
                if(aktualis.pozicio.x == peashooter.pozicio.x*(szeles/oszlop)){
                    if(peashooter.hp == 1)
                        peashooter_torol(j, &(novenyek->peashooters_din));
                    else
                        --novenyek -> peashooters_din.peashooters[j].hp;
                }
            }
        }
        for(int j = 0; j < novenyek->wallnuts_din.meret; ++i) {
            Wallnut wallnut = novenyek -> wallnuts_din.wallnuts[i];
            if(aktualis.pozicio.y == wallnut.pozicio.y){
                if(aktualis.pozicio.x == wallnut.pozicio.x){
                    if(wallnut.hp == 1)
                        wallnut_torol(j, &(novenyek->wallnuts_din));
                    else
                        --novenyek -> wallnuts_din.wallnuts[j].hp;
                }
            }
        }
        for(int j = 0; j < novenyek->sunflowers_din.meret; ++i) {
            Sunflower sunflower = novenyek -> sunflowers_din.sunflowers[i];
            if(aktualis.pozicio.y == sunflower.pozicio.y){
                if(aktualis.pozicio.x == sunflower.pozicio.x){
                    if(sunflower.hp == 1)
                        sunflower_torol(j, &(novenyek->sunflowers_din));
                    else
                        --novenyek -> sunflowers_din.sunflowers[j].hp;
                }
            }
        }
        zombik_din -> zombik[i].pozicio.x -= ZOMBIE_MOVE;
    }
}
/**
 *@brief Egy zombi t�rl�s��rt felel�s f�ggv�ny
 *
 *@param hanyadik Hanyadik zombit kell kit�r�lni a dinamikus t�mbb�l
 *@param zombi_din A zombikat tartalmaz� dinamikus t�mb
 */
void zombi_torol(int hanyadik, Zombi_din* zombi_din) {
    Zombi* uj = (struct Zombi*) malloc ((zombi_din -> meret-1) * sizeof(struct Zombi));
    int ujIndx = 0;
    for(int i = 0; i < zombi_din -> meret; ++i) {
        if(i != hanyadik) {
          uj[ujIndx++] = zombi_din -> zombik[i];
          ++ujIndx;
        }
    }
    zombi_din -> meret = ujIndx;
    free(zombi_din -> zombik);
    zombi_din -> zombik = uj;
}
/**
 *@brief Egy zombi id�z�s��rt felel�s f�ggv�ny
 *
 *@param hova Hova kell "spawn"-olni a zombit
 *@param zombi_din A zombikat tartalmaz� dinamikus t�mb
 */
void spawn_zombie(Pont hova, Zombi_din* zombies_din){
    Zombi* uj = (struct Zombi*) malloc ((zombies_din -> meret+1) * sizeof(struct Zombi));
    for(int i = 0; i < zombies_din -> meret; ++i) {
        uj[i] = zombies_din->zombik[i];
    }
    Zombi uj_zomb = {.hp = ZOMBIE_HP,
                .pozicio = hova};
    uj[zombies_din->meret] = uj_zomb;
    zombies_din -> meret += 1;
    free(zombies_din -> zombik);
    zombies_din -> zombik = uj;
    printf("zombie spawned eddigi zombie: %d",zombies_din -> meret);
}

