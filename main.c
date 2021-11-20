#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "jatekmenet.h"
#include "debugmalloc.h"
#include "megjelenit.h"
#include "plants.h"
#include "zombie.h"
#include "bullets.h"
/**
 *@file main.c
 *
 *
 */
enum {SOR = 5};
enum {OSZLOP = 9};

/* ablak letrehozasa */
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    if(IMG_Init(IMG_INIT_PNG) < 0) {
        SDL_Log("Nem hozhato letre a kep: %s", SDL_GetError());
        exit(1);
    }

    *pwindow = window;
    *prenderer = renderer;
}

Uint32 idozit(Uint32 ms, void *param){
    param = (void*)param;
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    Jatek uj;
    uj_jatek(&uj,9,5,640,420);

    uj.napocska = 1000;
    SelectedItem selectedItem = NOTHING;

    Pont zombie = {.x = 600, .y = 4};
    Pont bullet1 = {.x = 100, .y = 0};
    Pont bullet2 = {.x = 250, .y = 2};
    spawn_zombie(zombie, &(uj.zombik_din));
    spawn_lovedek(bullet1,&uj.lovedekek_din);
    spawn_lovedek(bullet2,&uj.lovedekek_din);

    /** ablak letrehozasa */
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("Plants vs Zombies nagyon bután", 640, 480, &window, &renderer);

    /** Időzítő hozzáadása*/
    SDL_TimerID id = SDL_AddTimer(20, idozit, NULL);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    Pont selected;
    Uint32 timeCounter = 0;
    bool quit = false;
    while(!quit) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type){
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode) {
                case SDL_SCANCODE_Q:
                    selectedItem = PEASHOOTER;
                    break;
                case SDL_SCANCODE_W:
                    selectedItem = WALLNUT;
                    break;
                case SDL_SCANCODE_E:
                    selectedItem = SUNFLOWER;
                    break;
                default:
                    selectedItem = NOTHING;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(selectedItem){
                case PEASHOOTER:
                    if(uj.napocska >= 100){
                        spawn_peashooter(selected, &uj.novenyek.peashooters_din);
                        uj.napocska -= 100;
                    }
                    break;
                case WALLNUT:
                    if(uj.napocska >= 50) {
                        spawn_wallnut(selected, &uj.novenyek.wallnuts_din);
                        uj.napocska -= 50;
                    }
                    break;
                case SUNFLOWER:
                    if(uj.napocska >= 25){
                        spawn_sunflower(selected, &uj.novenyek.sunflowers_din);
                        uj.napocska -= 25;
                    }
                    break;
                case NOTHING:
                    break;
                }
                break;
            case SDL_USEREVENT:
                 if(timeCounter == 50){
                    timeCounter = 0;
                    uj.time++;
                 }
                 jatek_kor(&uj);
                 timeCounter++;
                 break;
            default:
                break;

            }
            draw_background(renderer,uj.palya, SOR, OSZLOP);
            draw_peashooters(renderer, uj.palya, &(uj.novenyek.peashooters_din));
            draw_sunflowers(renderer, uj.palya, &(uj.novenyek.sunflowers_din));
            draw_wallnuts(renderer, uj.palya, &(uj.novenyek.wallnuts_din));
            draw_zombies(renderer, uj.palya,&(uj.zombik_din));
            draw_bullets(renderer,&uj.lovedekek_din,uj.palya[0][0].h);
            SDL_Rect current_rect = get_rect(uj.palya, SOR, OSZLOP, &selected);
            draw_selectedItem(renderer, current_rect ,selectedItem);
            SDL_RenderPresent(renderer);
        }
    }

    jatek_felszabadit(&uj);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_RemoveTimer(id);
    SDL_Quit();

    return 0;
}
