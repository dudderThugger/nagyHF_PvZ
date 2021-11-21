#ifndef BULLETS_H_INCLUDED
#define BULLETS_H_INCLUDED
/**
 *@file bullets.h
 *@brief L�ved�kekhez kapcsol�d� f�ggv�nyek deklar�ci�ja
 */
enum {BULLET_SPEED = 10};
void spawn_lovedek(Pont poz, Lovedek_list* lovedekek_list);
void lovedek_mozog(Lovedek_list* lovedekek_list, Zombie_list* zombik_list, int sor);

#endif // BULLETS_H_INCLUDED
