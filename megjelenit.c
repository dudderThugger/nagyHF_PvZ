#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <SDL_image.h>
#include "jatekmenet.h"
#include "debugmalloc.h"
#include "megjelenit.h"

/**
 *@file megjelenit.c
 *@brief Az egész játék megjelenítését végzõ függvények definicióját tartalmazó fájl
 *
 *A háttér kirajzolása, a különbözõ növények kirajzolása és egyéb grafikai függvényeket tartalmaz
 */

/**
 *@brief A háttér kirajzolását végzi el
 *
 *Négyzeteket rajzol a már korábban kiszámolt koordinátákra, és betölti a "HUD"-ot
 *@param renderer A renderer pointere
 *@param palya A palya négyzeteinek pointereit tartalmazó dinamikus tömb
 *@param sor A sorok száma
 *@param oszlop Az oszlopok száma
 */
void draw_background(SDL_Renderer *renderer, Rects** palya, int sor, int oszlop) {
    for(int i = 0; i < sor; ++i) {
        for(int j = 0; j < oszlop; ++j) {
            SDL_Rect temp = {.x = palya[i][j].x, .y = palya[i][j].y, .w = palya[i][j].w, palya[i][j].h};
            if(i%2 == 0){
                if((j%2 == 0))
                    SDL_SetRenderDrawColor(renderer, 0, 210, 0, 255);
                else
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                }
            else {
                if((j%2 == 1))
                    SDL_SetRenderDrawColor(renderer, 0, 210, 0, 255);
                else
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                }
        SDL_RenderFillRect(renderer, &temp);
        }
    }
    SDL_Texture* hud = IMG_LoadTexture(renderer,"hud.png");
    SDL_Rect hud_rect = {.x = 0, .y = 0, .h = 60, .w = 640};
    SDL_RenderCopy(renderer,hud,NULL,&hud_rect);
}
/**
 *@brief Az összes peashooter kirajzolását végző függvény
 *
 *@param renderer A rendererre mutató pointer
 *@param palya A palya téglalapjaira mutató, pointerek tömbje, amiből az adatokat szedjük a képek beillesztéséhez
 *@param peashooter_din a peashooterek dinamikus tömbje
 */
void draw_peashooters(SDL_Renderer * renderer, Rects** palya, Peashooter_din* peashooter_din){
    SDL_Texture *peashooter = IMG_LoadTexture(renderer, "peashooter.png");
    for(int i = 0; i < peashooter_din -> meret; ++i){
        SDL_Rect aktualis = {.x = palya[peashooter_din->peashooters[i].pozicio.y][peashooter_din->peashooters[i].pozicio.x].x,
                             .y = palya[peashooter_din->peashooters[i].pozicio.y][peashooter_din->peashooters[i].pozicio.x].y,
                             .h = palya[peashooter_din->peashooters[i].pozicio.y][peashooter_din->peashooters[i].pozicio.x].h,
                             .w = palya[peashooter_din->peashooters[i].pozicio.y][peashooter_din->peashooters[i].pozicio.x].w};
        SDL_RenderCopy(renderer,peashooter,NULL,&aktualis);
    }
    SDL_DestroyTexture(peashooter);
}
/**
 *@brief Az összes sunflower kirajzolását végző függvény
 *
 *@param renderer A rendererre mutató pointer
 *@param palya A palya téglalapjaira mutató, pointerek tömbje, amiből az adatokat szedjük a képek beillesztéséhez
 *@param sunflower_din a sunflowerek dinamikus tömbje
 */
void draw_sunflowers(SDL_Renderer * renderer, Rects** palya, Sunflower_din* sunflower_din){
    SDL_Texture *sunflower = IMG_LoadTexture(renderer, "sunflower.png");
    for(int i = 0; i < sunflower_din -> meret; ++i){
        SDL_Rect aktualis = {.x = palya[sunflower_din->sunflowers[i].pozicio.y][sunflower_din->sunflowers[i].pozicio.x].x,
                             .y = palya[sunflower_din->sunflowers[i].pozicio.y][sunflower_din->sunflowers[i].pozicio.x].y,
                             .h = palya[sunflower_din->sunflowers[i].pozicio.y][sunflower_din->sunflowers[i].pozicio.x].h,
                             .w = palya[sunflower_din->sunflowers[i].pozicio.y][sunflower_din->sunflowers[i].pozicio.x].w};
        SDL_RenderCopy(renderer,sunflower,NULL,&aktualis);
    }
    SDL_DestroyTexture(sunflower);
}
/**
 *@brief Az összes wallnut kirajzolását végző függvény
 *
 *@param renderer A rendererre mutató pointer
 *@param palya A palya téglalapjaira mutató, pointerek tömbje, amiből az adatokat szedjük a képek beillesztéséhez
 *@param wallnut_din a wallnutok dinamikus tömbje
 */
void draw_wallnuts(SDL_Renderer * renderer, Rects** palya, Wallnut_din* wallnuts_din){
    SDL_Texture *wallnut = IMG_LoadTexture(renderer, "wallnut.png");
    for(int i = 0; i < wallnuts_din -> meret; ++i){
        SDL_Rect aktualis = {.x = palya[wallnuts_din->wallnuts[i].pozicio.y][wallnuts_din->wallnuts[i].pozicio.x].x,
                             .y = palya[wallnuts_din->wallnuts[i].pozicio.y][wallnuts_din->wallnuts[i].pozicio.x].y,
                             .h = palya[wallnuts_din->wallnuts[i].pozicio.y][wallnuts_din->wallnuts[i].pozicio.x].h,
                             .w = palya[wallnuts_din->wallnuts[i].pozicio.y][wallnuts_din->wallnuts[i].pozicio.x].w};
        SDL_RenderCopy(renderer,wallnut,NULL,&aktualis);

    }
    SDL_DestroyTexture(wallnut);
}
/**
 *@brief Az összes zombi kirajzolását végző függvény
 *
 *@param renderer A rendererre mutató pointer
 *@param palya A palya téglalapjaira mutató, pointerek tömbje, amiből az adatokat szedjük a képek beillesztéséhez
 *@param zombies_din A zombik dinamikus tömbje
 */
void draw_zombies(SDL_Renderer* renderer, Rects** palya, Zombi_din* zombies_din) {
    SDL_Texture *zombie = IMG_LoadTexture(renderer, "zombie.png");
    SDL_SetTextureBlendMode(zombie, SDL_BLENDMODE_BLEND);
    for(int i = 0; i < zombies_din->meret; ++i) {
        SDL_Rect aktualis =     {.x = zombies_din -> zombik[i].pozicio.x,
                                .y = palya[zombies_din->zombik[i].pozicio.y][0].y,
                                .h = palya[zombies_din->zombik[i].pozicio.y][0].h,
                                .w = palya[zombies_din->zombik[i].pozicio.y][0].w};
        SDL_RenderCopy(renderer, zombie, NULL, &aktualis);
    }
    SDL_DestroyTexture(zombie);
}
/**
 *@brief A téglalap meghatározását végző függvény, amire az egér mutat
 *
 * A függvény lekéri az egér helyzetét és ezt követően egy dupla ciklusban meghatározza, melyik téglalapon helyezkedik el
 *@param palya A palya téglalapjaira mutató, pointerek tömbje, amiből az adatokat szedjük a képek beillesztéséhez
 *@param sor A sorok száma
 *@param oszlop Az oszlopok száma
 *@param selected A kiválasztott téglalap koordinátáit ebbe a pointerbe írjuk, így máshol is fel tudjuk használni
 */
SDL_Rect get_rect(Rects** palya, int sor, int oszlop, Pont* selected) {
    SDL_Rect pee;
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x,&mouse_y);
    for(int i = 0; i < sor; ++i) {
        for(int j = 0; j < oszlop; ++j) {
            if(palya[i][j].x <= mouse_x && mouse_x < palya[i][j].x+palya[i][j].w){
                if(palya[i][j].y < mouse_y && mouse_y < palya[i][j].y+palya[i][j].h){
                    pee.x = palya[i][j].x;
                    pee.y = palya[i][j].y;
                    pee.w = palya[i][j].w;
                    pee.h = palya[i][j].h;
                    selected -> x = j;
                    selected -> y = i;
                }

            }
        }
    }
    return pee;
}
/**
 *@brief Az éppen kiválasztott "item" megjelenítését végző függvény
 *
 *A függvény attól függően hogy melyik statebe van a selected Item változó, másik texturát töl be és jelenít meg
 *@param renderer A rendererre mutató pointer
 *@param rect Az aktuális téglalap amire az egerünk mutat
 *@param selectedItem A kiválasztott item, esetükben peashooter/ wallnut/ sunflower vagy semmi
 */
void draw_selectedItem(SDL_Renderer* renderer, SDL_Rect rect, SelectedItem selectedItem) {

    SDL_Texture* peashooter = IMG_LoadTexture(renderer, "peashooter.png");
    SDL_Texture* wallnut = IMG_LoadTexture(renderer, "wallnut.png");
    SDL_Texture* sunflower = IMG_LoadTexture(renderer, "sunflower.png");

    switch(selectedItem){
    case PEASHOOTER:
        SDL_RenderCopy(renderer,peashooter,NULL,&rect);
        break;
    case WALLNUT:
        SDL_RenderCopy(renderer,wallnut,NULL,&rect);
        break;
    case SUNFLOWER:
        SDL_RenderCopy(renderer,sunflower,NULL,&rect);
        break;
    default:
        return;
    }
    SDL_DestroyTexture(peashooter);
    SDL_DestroyTexture(wallnut);
    SDL_DestroyTexture(sunflower);
}
