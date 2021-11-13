#include <stdio.h>
#include <stdlib.h>
#include "jatekmenet.h"
#include "debugmalloc.h"

static void noveny_akciok(Novenyek* novenyek, Lovedek_din* lovedekek, int* napocska);
static void spawn_lovedek(Pont poz, Lovedek_din* lovedekek_din);
static void lovedek_mozog(Lovedek_din* lovedekek_din, Zombi_din* zombik_din, int sor);
static void zombi_akciok(Zombi_din* zombik_din, Novenyek* novenyek);
static void lovedek_torol(int hanyadik, Lovedek_din* lovedekek_din);
static void zombi_torol(int hanyadik, Zombi_din* zombi_din);
static void peashooter_torol(int hanyadik, Peashooter_din* peashooter_din);
static void wallnut_torol(int hanyadik, Wallnut_din* wallnut_din);
static void sunflower_torol(int hanyadik, Sunflower_din* sunflower_din);

// Uj jatek kezdese parameterkent a jatek strukturajat kapja,
// abban lefoglal a dinamikus tomboknek egy pointert, hogy a kesobbiekben egyszerubb legyen a kezeles
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
                    Rects akt = {.x = ((width/oszlop) * j), .y = ((height/sor) * i) + 60, .w = (width/oszlop), .h = (height/sor)};
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

// ez a fugveny fogja az egyes korben a kulonbozo allapotokat meghivni
// parameterkent megkapja a jatek strukturat
void jatek_kor(Jatek* game) {
    noveny_akciok(&(game -> novenyek), &(game -> lovedekek_din), &(game -> napocska));
    lovedek_mozog(&(game -> lovedekek_din), &(game-> zombik_din), game -> sor);
    zombi_akciok(&(game -> zombik_din), &(game->novenyek));
}

static void noveny_akciok(Novenyek* novenyek, Lovedek_din* lovedekek, int* napocska) {
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

static void spawn_lovedek(Pont poz, Lovedek_din* lovedekek_din){
    Lovedek* uj = (struct Lovedek*) malloc ((lovedekek_din -> meret+1) * sizeof(struct Lovedek));
    Lovedek ujLov = {poz};
    for(int i = 0; i < lovedekek_din -> meret; ++i) {
        uj[i] = lovedekek_din -> lovedekek[i];
    }
    uj[lovedekek_din -> meret + 1] = ujLov;
    free(lovedekek_din -> lovedekek);
    lovedekek_din -> lovedekek = uj;
}
static void lovedek_torol(int hanyadik, Lovedek_din* lovedekek_din) {
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

static void lovedek_mozog(Lovedek_din* lovedekek_din, Zombi_din* zombik_din, int sor){
    for(int i = 0; i < lovedekek_din -> meret; ++i){
        Pont aktualis = lovedekek_din -> lovedekek[i].pozicio;
        // Ha kier a lovedek toroljuk
        if(aktualis.x+1 > sor) {
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
static void zombi_akciok(Zombi_din* zombik_din, Novenyek* novenyek){
    for(int i = 0; i <  zombik_din -> meret; ++i) {
        Zombi aktualis = zombik_din -> zombik[i];
        // Zombi beer
        if(aktualis.pozicio.x == 0)
            zombi_torol(i, zombik_din);
        // Zombi novenynel van
        for(int j = 0; j < novenyek->peashooters_din.meret; ++i) {
            Peashooter peashooter = novenyek -> peashooters_din.peashooters[i];
            if(aktualis.pozicio.y == peashooter.pozicio.y){
                if(aktualis.pozicio.x == peashooter.pozicio.x){
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
        // Zombi lep
        --zombik_din -> zombik[i].pozicio.x;
    }
}

static void zombi_torol(int hanyadik, Zombi_din* zombi_din) {
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

static void peashooter_torol(int hanyadik, Peashooter_din* peashooter_din){
    Peashooter* uj = (struct Peashooter*) malloc ((peashooter_din -> meret-1) * sizeof(struct Peashooter));
    int ujIndx = 0;
    for(int i = 0; i < peashooter_din -> meret; ++i) {
        if(i != hanyadik) {
          uj[ujIndx++] = peashooter_din -> peashooters[i];
          ++ujIndx;
        }
    }
    peashooter_din -> meret = ujIndx;
    free(peashooter_din -> peashooters);
    peashooter_din -> peashooters = uj;
}

static void wallnut_torol(int hanyadik, Wallnut_din* wallnut_din){
    Wallnut* uj = (struct Wallnut*) malloc ((wallnut_din -> meret-1) * sizeof(struct Wallnut));
    int ujIndx = 0;
    for(int i = 0; i < wallnut_din -> meret; ++i) {
        if(i != hanyadik) {
          uj[ujIndx++] = wallnut_din -> wallnuts[i];
          ++ujIndx;
        }
    }
    wallnut_din -> meret = ujIndx;
    free(wallnut_din -> wallnuts);
    wallnut_din -> wallnuts = uj;
}

static void sunflower_torol(int hanyadik, Sunflower_din* sunflower_din){
    Sunflower* uj = (Sunflower*) malloc ((sunflower_din -> meret-1) * sizeof(struct Sunflower));
    int ujIndx = 0;
    for(int i = 0; i < sunflower_din -> meret; ++i) {
        if(i != hanyadik) {
          uj[ujIndx++] = sunflower_din -> sunflowers[i];
          ++ujIndx;
        }
    }
    sunflower_din -> meret = ujIndx;
    free(sunflower_din -> sunflowers);
    sunflower_din -> sunflowers = uj;
}
