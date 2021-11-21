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
    printf("bullet spawned!\n");
    Lovedek* uj = (struct Lovedek*) malloc (sizeof(struct Lovedek));
    uj->next = NULL;
    Lovedek* iter = lovedek_list->first;
    if(iter == NULL){
        lovedek_list->first = uj;
        uj->prev = NULL;
    } else {
        while(iter->next != NULL)
            iter = iter->next;
        iter->next = uj;
    }
    lovedek_list->meret += 1;
}
 /**
  *@brief Egy lövedék törlése
  *@param hanyadik Hanyadik lövedéket kell törölni a dinamikus tömbből
  *@param lovedekek_din A lövedékeket tartalmazó dinamikus tömb
  */
void lovedek_torol(Lovedek* del, Lovedek_list* lovedek_list) {
    if(del->prev == NULL)
        lovedek_list->first = NULL;
    del->prev->next= del->next;
    del->next->prev= del->prev;
    lovedek_list->meret -= 1;
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
        while(iterZ != NULL){
            if(iterZ->pozicio.x - iterL->pozicio.x < 10 && iterL->pozicio.y == iterZ->pozicio.y){
                Lovedek* next = iterL->next;
                lovedek_torol(iterL,lovedekek_list);
                iterZ->hp -= 1;
                iterL = next;
                mozog = false;
            }
        }
        /** A lövedék kiér a pályáról */
        if(mozog && iterL >= szeles) {
            Lovedek* next = iterL->next;
            lovedek_torol(iterL,lovedekek_list);
            iterL = next;
            mozog = false;
        }
        /** A lövedék mozog*/
        if(mozog){
            iterL->pozicio.x += BULLET_SPEED;
        }
        mozog = true;
    }
}