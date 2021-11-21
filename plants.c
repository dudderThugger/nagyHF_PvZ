#include <stdio.h>
#include <stdlib.h>
#include "jatekmenet.h"
#include "debugmalloc.h"
#include "plants.h"
#include "bullets.h"

void spawn_peashooter(Pont pont, Peashooter_list* peashooter_list){
    Peashooter* uj = (Peashooter*) malloc (sizeof(Peashooter));
    uj->prev = NULL;
    if(peashooter_list->meret = 0){
        uj->next = NULL;
    } else {
        peashooter_list->first->prev = uj;
        uj->next = peashooter_list->first;
    }
    uj->pozicio = pont;
    peashooter_list->meret += 1;
    peashooter_list->first = uj;
}
void spawn_wallnut(Pont pont, Wallnut_list* wallnut_list){
    Wallnut* uj = (Wallnut*) malloc (sizeof(Wallnut));
    uj->prev = NULL;
    if(wallnut_list->meret = 0){
        uj->next = NULL;
    } else {
        wallnut_list->first->prev = uj;
        uj->next = wallnut_list->first;
    }
    uj->pozicio = pont;
    wallnut_list->meret += 1;
    wallnut_list->first = uj;
}
void spawn_sunflower(Pont pont, Sunflower_list* sunflower_list){
    Sunflower* uj = (Sunflower*) malloc (sizeof(Sunflower));
    uj->prev = NULL;
    if(sunflower_list->meret = 0){
        uj->next = NULL;
    } else {
        sunflower_list->first->prev = uj;
        uj->next = sunflower_list->first;
    }
    uj->pozicio = pont;
    sunflower_list->meret += 1;
    sunflower_list->first = uj;
}
void delete_peashooter(Peashooter* del, Peashooter_list* peashooter_list){
    if(del->prev == NULL)
        peashooter_list->first = NULL;
    del->prev->next= del->next;
    del->next->prev= del->prev;
    peashooter_list->meret -= 1;
    free(del);
}
void delete_sunflower(Sunflower* del, Sunflower_list* sunflower_list){
    if(del->prev == NULL)
        sunflower_list->first = NULL;
    del->prev->next= del->next;
    del->next->prev= del->prev;
    sunflower_list->meret -= 1;
    free(del);
}
void delete_wallnut(Wallnut* del, Wallnut_list* wallnut_list){
    if(del->prev == NULL)
        wallnut_list->first = NULL;
    del->prev->next= del->next;
    del->next->prev= del->prev;
    wallnut_list->meret -= 1;
    free(del);
}
void plant_actions(Novenyek* novenyek, Lovedek_list* lovedek_list, int width, int column, int* napocska){
    Peashooter* iterP = novenyek->peashooters_list.first;
    Sunflower* iterS = novenyek->sunflowers_list.first;
    Wallnut* iterW = novenyek->wallnuts_list.first;
    /** Peashooterek akciói*/
    while(iterP != NULL){
        /** Él-e még a növény?*/
        if(iterP->hp <= 0){
            Peashooter* next = iterP->next;
            delete_peashooter(iterP,&novenyek->peashooters_list);
            iterP = next;
        }else{
        /** Lövés*/
            if(iterP->action_time == 0) {
                Pont p = {.x = (width/column)*iterP->pozicio.x, .y = iterP->pozicio.y};
                spawn_lovedek(p, lovedek_list);
                iterP->action_time = PEASHOOTER_ACTION_TIME;
            } else {
                iterP->action_time--;
            }
            iterP = iterP->next;
        }
    }
    /** Sunflowerek akciói */
    while(iterS != NULL){
        /** Él-e még a növény?*/
        if(iterS->hp <= 0){
            Sunflower* next = iterS->next;
            delete_sunflower(iterS,&novenyek->sunflowers_list);
            iterS = next;
        }else{
        /** Napocska adás*/
            if(iterS->action_time == 0) {
                napocska += 25;
                iterS->action_time = SUNFLOWER_ACTION_TIME;
            } else {
                iterS->action_time -= 1;
            }
            iterS = iterS->next;
        }
    }
    while(iterW != NULL){
        if(iterW->hp <= 0){
            Wallnut* next = iterW->next;
            delete_wallnut(iterW,&novenyek->wallnuts_list);
            iterW = next;
        } else {
            iterW = iterW->next;
        }
    }
}