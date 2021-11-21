#include <stdio.h>
#include <stdlib.h>
#include "jatekmenet.h"
#include "debugmalloc.h"
#include "plants.h"
#include "bullets.h"
#include "zombie.h"

bool van_noveny (Pont p, Novenyek* novenyek, Rects** palya, Peashooter** pea, Wallnut** wall, Sunflower** sun){
    Peashooter* iterP = novenyek->peashooters_list.first;
    Sunflower* iterS = novenyek->sunflowers_list.first;
    Wallnut* iterW = novenyek->wallnuts_list.first;
    bool van = false;
    while(iterP!=NULL){
        if(palya[iterP->pozicio.x][iterP->pozicio.y].y == p.y && palya[iterP->pozicio.x][iterP->pozicio.y].y == p.y){
            *pea = iterP;
            return true;
        }
        iterP = iterP->next;
    }
    while(iterS!=NULL){
        if(palya[iterS->pozicio.x][iterS->pozicio.y].y == p.y && palya[iterS->pozicio.x][iterS->pozicio.y].y == p.y){
            *sun = iterS;
            return true;
        }
        iterS = iterS->next;
    }
    while(iterW!=NULL){
        if(palya[iterW->pozicio.x][iterW->pozicio.y].y == p.y && palya[iterW->pozicio.x][iterW->pozicio.y].y == p.y){
            *wall = iterW;
            return true;
        }
        iterW = iterW->next;
    }
    return van;
}

void delete_zombie(Zombi* del, Zombie_list* zombie_list){
    if(del->prev == NULL)
        zombie_list->first = NULL;
    del->prev->next= del->next;
    del->next->prev= del->prev;
    zombie_list->meret -= 1;
    free(del);
}

void spawn_zombie(Zombie_list* zombie_list, Pont pont){
    Zombi* uj = (Zombi*) malloc (sizeof(Zombi));
    uj->prev = NULL;
    if(zombie_list->meret = 0){
        uj->next = NULL;
    } else {
        zombie_list->first->prev = uj;
        uj->next = zombie_list->first;
    }
    uj->hp = ZOMBIE_HP;
    uj->pozicio = pont;
    zombie_list->meret += 1;
    zombie_list->first = uj;
    printf("SPaWnsn!\n");
}

void zombie_spawner (int time, Zombie_list* zombie_list, int width){
    if(time % ZOMBIE_SPAWN_TIME == 1) {
        int random = rand()%3;
        for(int i = 0; i < (time/ZOMBIE_SPAWN_TIME) + 1; ++i){
            Pont pont = {.x = width, .y = (random+i)%5};
            spawn_zombie(zombie_list, pont);
        }
    }
}
void zombie_actions(Zombie_list* zombie_list, Novenyek* novenyek, Rects** palya, int* life) {
    Zombi* iter = zombie_list->first;
    bool move = true;
    while(iter != NULL){
        /** Él-e még?*/
        if(iter->hp <= 0){
            Zombi* del = iter;
            iter = iter->next;
            delete_zombie(del, zombie_list);
        }
        /** Novenynel van*/
        Peashooter* p = NULL;
        Wallnut* w = NULL;
        Sunflower* s = NULL;
        if(van_noveny(iter->pozicio, novenyek, palya,&p,&w,&s)){
            move = false;
            if(p != NULL)
                p->hp -= 1;
            else if(w != NULL)
                w->hp -= 1;
            else if(s != NULL)
                s->hp -= 1;
            iter = iter->next;
        }
        if(move){
            iter->pozicio.x -= ZOMBIE_MOVE;
            iter = iter->next;
        }
        move = true;
    }
}