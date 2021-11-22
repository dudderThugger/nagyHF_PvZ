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
    while(iterP!=NULL){
        if(iterP->pozicio.y == p.y && (p.x - palya[iterP->pozicio.y][iterP->pozicio.x].x) <= 15){
            *pea = iterP;
            return true;
        }
        iterP = iterP->next;
    }
    while(iterS!=NULL){
        if(iterS->pozicio.y == p.y && (p.x - palya[iterS->pozicio.y][iterS->pozicio.x].x) <= 15){
            *sun = iterS;
            return true;
        }
        iterS = iterS->next;
    }
    while(iterW!=NULL){
        if(iterW->pozicio.y == p.y && (p.x - palya[iterW->pozicio.y][iterW->pozicio.x].x) <= 15){
            *wall = iterW;
            return true;
        }
        iterW = iterW->next;
    }
    return false;
}

void delete_zombie(Zombi* del, Zombie_list* zombie_list){
    if(del->prev == NULL) {
        if(del->next == NULL){
            zombie_list->first = NULL;
        } else {
            zombie_list->first = del->next;
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

void spawn_zombie(Zombie_list* zombie_list, Pont pont){
    Zombi* uj = (Zombi*) malloc (sizeof(Zombi));
    uj->prev = NULL;
    if(zombie_list->first == NULL){
        uj->next = NULL;
    } else {
        zombie_list->first->prev = uj;
        uj->next = zombie_list->first;
    }
    uj->hp = ZOMBIE_HP;
    uj->pozicio = pont;
    zombie_list->first = uj;
}

void zombie_spawner (int time, Zombie_list* zombie_list, int width,int sor){
    int random = rand()%3;
    for(int i = 0; i < (time/ZOMBIE_SPAWN_TIME) + 1; ++i){
        Pont pont = {.x = width, .y = (random+i)%sor};
        spawn_zombie(zombie_list, pont);
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
            move = false;
        }
        /** Novenynel van*/
        Peashooter* p = NULL;
        Wallnut* w = NULL;
        Sunflower* s = NULL;
        if(move && van_noveny(iter->pozicio, novenyek, palya,&p,&w,&s)){
            move = false;
            if(p != NULL)
                p->hp -= 1;
            else if(w != NULL)
                w->hp -= 1;
            else if(s != NULL)
                s->hp -= 1;
            iter = iter->next;
        }
        /** Eleri a szelet*/
        if(move && iter->pozicio.x < 0) {
            Zombi* del = iter;
            iter = iter->next;
            delete_zombie(del, zombie_list);
            move = false;
        }
        if(move){
            iter->pozicio.x -= ZOMBIE_MOVE;
            iter = iter->next;
        }
        move = true;
    }
}