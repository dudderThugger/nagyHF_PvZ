#include <stdio.h>
#include <stdlib.h>
#include "jatekmenet.h"
#include "debugmalloc.h"
#include "plants.h"
#include "bullets.h"

/**
 *@file plants.h
 *@brief A n�v�nyekhez kapcsol�d� f�ggv�nyek defeinici�ja
 *
 * Tartalmazza az �sszes n�v�ny akci�j��rt felel�s f�ggv�nyt, a k�l�nb�z� n�v�nyek
 * teremt�s��rt felel�s f�ggv�nyeket �s a k�l�nb�z� n�v�nyek t�rl�s�t v�gz� f�ggv�nyeket. *
 */

 /**
  *@brief A n�v�nyek akci�j�t v�gz� f�ggv�ny
  *
  *A k�t akci�val rendelkez� n�v�ny akci�j�t elv�gzi, ha azoknak az akci� idej�k �ppen 0-n�l van
  *@param novenyek A n�v�nyek dinamikus t�mbjeit tartalmaz� strukt�ra
  *@param lovedekek A l�ved�keket tartalmazo dinamiku t�mb
  *@param napocska A napocsk�k sz�m�t t�rol� integer pointere
  */
void noveny_akciok(Novenyek* novenyek, Lovedek_din* lovedekek, int* napocska) {
    for(int i = 0; i < novenyek -> peashooters_din.meret; ++i) {
        if(novenyek -> peashooters_din.peashooters[i].action_time == 0){
            spawn_lovedek(novenyek -> peashooters_din.peashooters[i].pozicio, lovedekek);
            novenyek -> peashooters_din.peashooters[i].action_time = 3;
        } else {
            --novenyek -> peashooters_din.peashooters[i].action_time;
        }
    }
    for(int i = 0; i < novenyek -> sunflowers_din.meret; ++i) {
        if(novenyek -> sunflowers_din.sunflowers[i].action_time == 0){
            *napocska += 25;
            novenyek -> sunflowers_din.sunflowers[i].action_time = 10;
        } else {
            --novenyek -> sunflowers_din.sunflowers[i].action_time;
        }
    }
}

/**
 *@brief Egy darab peashooter t�rl�s�t v�gz� f�ggv�ny
 *@param hanyadik H�nyadik elemet kell t�r�lni a dinamikus t�mbb�l
 *@param peashooter_din A peashootereket tartalmaz� dinamikus t�mb
 */
void peashooter_torol(int hanyadik, Peashooter_din* peashooter_din){
    Peashooter* uj = (struct Peashooter*) malloc ((peashooter_din -> meret-1) * sizeof(struct Peashooter));
    int ujIndx = 0;
    for(int i = 0; i < peashooter_din -> meret; ++i) {
        if(i != hanyadik) {
          uj[ujIndx++] = peashooter_din -> peashooters[i];
          ++ujIndx;
        }
    }
    peashooter_din -> meret -= 1;
    free(peashooter_din -> peashooters);
    peashooter_din -> peashooters = uj;
}

/**
 *@brief Egy darab wallnut t�rl�s�t v�gz� f�ggv�ny
 *@param hanyadik H�nyadik elemet kell t�r�lni a dinamikus t�mbb�l
 *@param wallnut_din A wallnutokat tartalmaz� dinamikus t�mb
 */
void wallnut_torol(int hanyadik, Wallnut_din* wallnut_din){
    Wallnut* uj = (struct Wallnut*) malloc ((wallnut_din -> meret-1) * sizeof(struct Wallnut));
    int ujIndx = 0;
    for(int i = 0; i < wallnut_din -> meret; ++i) {
        if(i != hanyadik) {
          uj[ujIndx++] = wallnut_din -> wallnuts[i];
          ++ujIndx;
        }
    }
    wallnut_din -> meret -=1;
    free(wallnut_din -> wallnuts);
    wallnut_din -> wallnuts = uj;
}

/**
 *@brief Egy darab sunflower t�rl�s�t v�gz� f�ggv�ny
 *@param hanyadik H�nyadik elemet kell t�r�lni a dinamikus t�mbb�l
 *@param sunflower_din A sunflowereket tartalmaz� dinamikus t�mb
 */
void sunflower_torol(int hanyadik, Sunflower_din* sunflower_din){
    Sunflower* uj = (Sunflower*) malloc ((sunflower_din -> meret-1) * sizeof(struct Sunflower));
    int ujIndx = 0;
    for(int i = 0; i < sunflower_din -> meret; ++i) {
        if(i != hanyadik) {
          uj[ujIndx++] = sunflower_din -> sunflowers[i];
          ++ujIndx;
        }
    }
    sunflower_din -> meret -=1;
    free(sunflower_din -> sunflowers);
    sunflower_din -> sunflowers = uj;
}
/**
 *@brief Egy peashooter teremt�s��rt felel�s f�ggv�ny
 *@param poz Melyik t�glalapon van a peashootert
 *@param peashooters A peashooterek dinamikus t�mbje
 */
void spawn_peashooter(Pont poz, Peashooter_din* peashooters) {
    Peashooter* uj = (Peashooter*) malloc ((peashooters -> meret + 1) * sizeof(Peashooter));
    for(int i = 0; i < peashooters -> meret; ++i) {
        uj[i] = peashooters -> peashooters[i];
    }
    free(peashooters->peashooters);
    Peashooter uj_pee = {.hp = 5, .pozicio = poz, .action_time = 3};
    uj[peashooters ->meret] = uj_pee;
    peashooters -> meret += 1;
    peashooters -> peashooters = uj;
    printf("spawned peashooter x:%d  y:%d  eddigi peashooter: %d\n",uj_pee.pozicio.x, uj_pee.pozicio.y, peashooters->meret);
}

void spawn_sunflower(Pont poz, Sunflower_din* sunflowers) {
    Sunflower* uj = (Sunflower*) malloc ((sunflowers -> meret + 1) * sizeof(Sunflower));
    for(int i = 0; i < sunflowers -> meret; ++i) {
        uj[i] = sunflowers -> sunflowers[i];
    }
    free(sunflowers->sunflowers);
    Sunflower uj_pee = {.hp = 5, .pozicio = poz, .action_time = 3};
    uj[sunflowers ->meret] = uj_pee;
    sunflowers -> meret += 1;
    sunflowers -> sunflowers = uj;
    printf("spawned sunflower x:%d  y:%d  eddigi sunflower: %d\n",uj_pee.pozicio.x, uj_pee.pozicio.y, sunflowers->meret);
}

void spawn_wallnut(Pont poz, Wallnut_din* wallnuts) {
    Wallnut* uj = (Wallnut*) malloc ((wallnuts -> meret + 1) * sizeof(Wallnut));
    for(int i = 0; i < wallnuts -> meret; ++i) {
        uj[i] = wallnuts -> wallnuts[i];
    }
    free(wallnuts->wallnuts);
    Wallnut uj_pee = {.hp = 5, .pozicio = poz};
    uj[wallnuts ->meret] = uj_pee;
    wallnuts -> meret += 1;
    wallnuts -> wallnuts = uj;
    printf("spawned sunflower x:%d  y:%d  eddigi wallnut: %d\n",uj_pee.pozicio.x, uj_pee.pozicio.y, wallnuts->meret);
}
