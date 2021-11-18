#ifndef JATEKMENET_H_INCLUDED
#define JATEKMENET_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "jatekmenet.h"

/**
 *@file jatekmenet.h
 *@brief Tartalmazza a j�t�kmenet�rt felel�s f�ggv�nyek deklar�ci�j�t �s a j�t�kban haszn�lt strukt�r�k z�m�t
 */

/**
 *@brief Egy n�gyzet elhelyezked�s�t t�rolja a p�ly�n
 *
 */
// Egy pont a palyan, ezen lehetnek novenyek, lovedekek, vagy zombik
typedef struct Pont {
    /** A n�gyzet oszlop �s sora*/
    int x, y;
} Pont;

/**
 *@brief Egy t�glalap adatait t�rol� strukt�ra
 */
typedef struct Rects {
    /** Egy t�glalap x, y koordin�t�ja sz�less�ge �s magass�ga*/
    int x, y, w, h;
} Rects;

/**
 *@brief Egy zombi adatait t�rol� strukt�ra
 */
typedef struct Zombi {
    /** A zombi �lete*/
    int hp;
    /** A zombi elhelyezked�se a p�ly�n (melyik n�gyzetbe van)*/
    Pont pozicio;
}Zombi;

/**
 *@brief A zombikat tartalmaz� dinamikus t�mb
 */
typedef struct Zombi_din {
    /** A zombik strukt�r�j�nak t�mbj�re mutat� pointer*/
    Zombi* zombik;
    /** A m�rete a t�mbnek*/
    int meret;
} Zombi_din;

/**
 *@brief Egy lovedek adatai
 */
typedef struct Lovedek {
    /**Pozici�ja a p�ly�n*/
    Pont pozicio;
} Lovedek;
/**
 *@brief A l�ved�kek dinamikus t�mbje
 */
typedef struct Lovedek_din {
    /** A loved�kek t�mbj�re mutat� pointer*/
    Lovedek* lovedekek;
    /**A dinamikus t�mb m�rete*/
    int meret;
} Lovedek_din;

/**
 *@brief Egy peashooter adatait tartalmaz� strukt�ra
 */
typedef struct Peashooter {
    /**A peashooter �lete*/
    int hp;
    /**A peashooter l�v�s�ig h�tral�v� id�*/
    int action_time;
    /**Pozici�ja a p�ly�n, h�nyadik oszlop, h�nyadik sor*/
    Pont pozicio;
} Peashooter;
/**
 *@brief A peashootereket tartalmaz� dinamikus t�mb strukt�r�ja
 */
typedef struct Peashooter_din {
    /**A peashooterek t�mbj�re mutat� pointer*/
    Peashooter* peashooters;
    /**A t�mb m�rete*/
    int meret;
} Peashooter_din;
/**
 *@bief Egy di�/krumpli adatait tartalmaz� strukt�ra
 */
typedef struct Wallnut {
    /** A krumpli aktu�lis �lete*/
    int hp;
    /** A krumpli pozici�ja, oszlop, sor*/
    Pont pozicio;
} Wallnut;
/**
 *@brief A krumplikat tartalmaz� dinamikus t�mb
 */
typedef struct Wallnut_din {
    /** A krumplikat tartalmaz� t�mbre mutat� pointer*/
    Wallnut* wallnuts;
    /** A t�mb m�rete*/
    int meret;
} Wallnut_din;
/**
 *@brief Egy napraforg� strukt�r�ja
 */
typedef struct Sunflower {
    /** A napraforg� aktu�lis �lete*/
    int hp;
    /** A napraforg� akci�j�ig mennyi id� van*/
    int action_time;
    /** A napraforg� pozici�ja*/
    Pont pozicio;
} Sunflower;
/**
 *@brief A napraforg�kat tartalmaz� dinamikus t�mb
 */
typedef struct Sunflower_din {
    /** A napraforg�k t�mbj�re mutat� pointer*/
    Sunflower* sunflowers;
    /**A t�mb m�rete*/
    int meret;
} Sunflower_din;
/**
 *@brief A k�l�nb�z� n�v�nyek dinamikus t�mbjeit tartalmaz� strukt�ra
 */
typedef struct Novenyek {
    /** A peashooterek dinamikus t�mbje*/
    Peashooter_din peashooters_din;
    /** A wallnutok dinamikus t�mbje*/
    Wallnut_din wallnuts_din;
    /** A sunbflower-ek dinamikus t�mbje*/
    Sunflower_din sunflowers_din;
} Novenyek;

/**
 *@brief Egy j�t�kmenet minden adat�t t�rolja
 *
 * Ezzel az egy strukt�r�val le�rhat� a j�t�k
 */
typedef struct Jatek {
    /** A j�t�k t�glalapjai, ezen vannak a n�v�nyek*/
    Rects** palya;
    /** A sorok sz�ma*/
    int sor;
    /** Az oszlopok sz�ma*/
    int oszlop;
    /** Az ablak magass�ga*/
    int h;
    /** Az ablak sz�less�ge*/
    int w;
    /** Mennyi ideje fut a j�t�k*/
    int time;
    /** Hany eleted maradt*/
    int elet;
    /** Az aktu�lis pontsz�mod*/
    int pont;
    /** Az aktu�lis napocsk�idnak a sz�ma*/
    int napocska;
    /** A n�v�nyek dinamikus t�mbjeit t�rol� strukt�ra*/
    Novenyek novenyek;
    /** A zombik dinamikus t�mbje*/
    Zombi_din zombik_din;
    /** A l�ved�kek dinamikus t�mbje*/
    Lovedek_din lovedekek_din;
} Jatek;

bool uj_jatek(Jatek* game, double sor, double oszlop, double w, double h);
void jatek_felszabadit (Jatek* game);
void jatek_kor(Jatek* game);

#endif // JATEKMENET_H_INCLUDED
