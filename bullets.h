#ifndef BULLETS_H_INCLUDED
#define BULLETS_H_INCLUDED
/**
 *@file bullets.h
 *@brief Lövedékekhez kapcsolódó függvények deklarációja
 */
void spawn_lovedek(Pont poz, Lovedek_din* lovedekek_din);
void spawn_lovedek(Pont poz, Lovedek_din* lovedekek_din);
void lovedek_mozog(Lovedek_din* lovedekek_din, Zombi_din* zombik_din, int sor);

#endif // BULLETS_H_INCLUDED
