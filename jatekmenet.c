#include <stdio.h>
#include <stdlib.h>
#include "jatekmenet.h"
#include "debugmalloc.h"
#include "plants.h"
#include "bullets.h"
#include "zombie.h"

/**
 *@file jatekmenet.c
 *@brief A j�t�k �ll�s�nak manipul�l�s�hoz k�thet� legfontosabb f�ggv�nyeket t�rolja
 *
 * A j�t�k l�trehoz�s�t �s ment�s�t, a dics�s�glista ir�ny�t�s�t, a men� ir�ny�t�s�t,
 * a j�t�k �ltal haszn�lt dinamikus t�mb�k felszabad�t�s�t v�gz� f�ggv�nyek mind itt tal�lhat�ak meg
 */
/**
 *@brief A j�t�k legelej�n ez a f�ggv�ny v�gzi el a j�t�k kezd�s�hez sz�ks�ges l�p�seket
 *
 * L�trehozza a p�lya t�glalapjait t�rol� dinamikus t�mb�t �s felt�lti a t�glalapok adataival
 * L�trehoz pointereket a dinamikus t�mb�kh�z, hogy k�s�bb k�nnyebben kezelhet� legyen
 * Be�ll�tja a kezd��rt�keket (pl. id�, pont)
 *@param game A j�t�kot tartalmaz� strukt�ra, amit m�dos�tunk
 *@param oszlop Az oszlopok sz�ma (az�rt val�s, hogy az oszt�sn�l elker�lj�k az esetleges kerek�t�seket)
 *@param sor A sorok sz�ma
 *@param width Az ablak sz�less�ge
 *@param height Az ablak magass�ga
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
/**
 *@brief A j�t�k �ltal haszn�lt dinamikus t�mb�k felszabad�t�sa
 *@param game A j�t�kot t�rol� strukt�ra
 */
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

/**
 *@brief A j�t�k egy k�r�t elv�gz� f�ggv�ny
 *@param game A j�t�k strukt�r�ja
 */
void jatek_kor(Jatek* game) {
    noveny_akciok(&(game -> novenyek), &(game -> lovedekek_din), &(game -> napocska));
    lovedek_mozog(&(game -> lovedekek_din), &(game-> zombik_din), game -> sor);
    zombi_akciok(&(game -> zombik_din), &(game->novenyek), &(game->elet), game->w, game->oszlop);
}
