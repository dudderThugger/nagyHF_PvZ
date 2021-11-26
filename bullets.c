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
 * A lövedékek mozgatásáért, idézéséért és törléséért felelős függvények
 */

 /**
  *@brief Egy lövedék idézése
  *@param poz A pont (téglalap helyzete) ahol a lövedék teremtődni fog
  *@param lovedekek_din A lövedékeket tartalmazó dinamikus tömb
  */
void spawn_lovedek(Pont poz, Lovedek_list* lovedek_list){
    Lovedek* uj = (struct Lovedek*) malloc (sizeof(struct Lovedek));
    uj->prev = NULL;
    uj->pozicio = poz;
    if(lovedek_list->first == NULL){
        uj->next = NULL;
    }else{
        lovedek_list->first->prev = uj;
        uj->next = lovedek_list->first;
    }
    lovedek_list->first = uj;
}
 /**
  *@brief Egy lövedék törlése
  *@param hanyadik Hanyadik lövedéket kell törölni a dinamikus tömbből
  *@param lovedekek_din A lövedékeket tartalmazó dinamikus tömb
  */
void lovedek_torol(Lovedek* del, Lovedek_list* lovedek_list) {
    if(del->prev == NULL) {
        if(del->next == NULL){
            lovedek_list->first = NULL;
        } else {
            lovedek_list->first = del->next;
            del->next->prev = NULL;
        }
    }else{
        if(del->next == NULL){
            del->prev->next = NULL;
        }
        else{
            del->prev->next = del->next;
            del->next->prev = del->prev;
        }
    }
    free(del);
}

/**
  *@brief Az összes lövedék mozgatása
  *@param lovedekek_din A lövedékeket tartalmazó dinamikus tömb
  *@param zombik_din A zombikat tartalmazó dinamikus tömb
  *@param oszlop A pálya szelessege, ha ezen túl megy törölni kell
  */
void lovedek_mozog(Lovedek_list* lovedekek_list, Zombie_list* zombik_list, int szeles){
    Lovedek* iterL = lovedekek_list->first;
    bool mozog= true;
    while(iterL != NULL){
        Zombi* iterZ = zombik_list->first;
        /** A lövedék zombinál van*/
        while(iterZ != NULL && mozog){
            if(iterZ->pozicio.x - iterL->pozicio.x <= 8 && iterL->pozicio.y == iterZ->pozicio.y){
                Lovedek* del = iterL;
                iterL = iterL->next;
                lovedek_torol(del,lovedekek_list);
                iterZ->hp -= 1;
                mozog = false;
            }
            iterZ = iterZ->next;
        }
        /** A lövedék kiér a pályáról */
        if(mozog && iterL->pozicio.x >= szeles) {
            Lovedek* del = iterL;
            iterL = iterL->next;
            lovedek_torol(del, lovedekek_list);
            mozog = false;

        }
        /** A lövedék mozog*/
        if(mozog){
            iterL->pozicio.x += BULLET_SPEED;
            iterL = iterL->next;
        }
        mozog = true;
    }
}