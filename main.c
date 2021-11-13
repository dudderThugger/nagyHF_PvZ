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
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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


int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    Jatek uj;
    uj_jatek(&uj,9,5,640,420);

    SelectedItem selectedItem = NOTHING;

    /* ablak letrehozasa */
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("SDL peldaprogram", 640, 480, &window, &renderer);



    SDL_Texture *peashooter = IMG_LoadTexture(renderer, "C:\\Users\\Szelestey\\Desktop\\egyetem\\prog1\\NHF\\sdl\\sdl_nagyHF\\pics\\peashooter.png");
    if(peashooter == NULL){
        SDL_Log("Nem tudta megnyitni a kepet: %s\n", SDL_GetError());
    }



    /**
         * Draw background
         */

    SDL_RenderPresent(renderer);

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

                break;
            case SDL_MOUSEBUTTONUP:

                break;
            default:
                break;

            }
            draw_background(renderer, uj.palya, SOR, OSZLOP);
            (selectedItem == NOTHING) ? printf("?\n"): printf("!\n");
            /*
            int mouse_x;
            int mouse_y;

            if(mouseStates[SDL_BUTTON_LEFT].held) {
                SDL_Rect pee;
                if(mouseStates[SDL_BUTTON_LEFT].held){
                    SDL_GetMouseState(&mouse_x,&mouse_y);
                    for(int i = 0; i < SOR; ++i) {
                        for(int j = 0; j < OSZLOP; ++j) {
                            if(uj.palya[i][j].x < mouse_x && mouse_x < uj.palya[i][j].x+uj.palya[i][j].w){
                                if(uj.palya[i][j].y < mouse_y && mouse_y < uj.palya[i][j].y+uj.palya[i][j].h){
                                    pee.x = uj.palya[i][j].x;
                                    pee.y = uj.palya[i][j].y;
                                    pee.w = uj.palya[i][j].w;
                                    pee.h = uj.palya[i][j].h;
                                }

                            }
                        }
                    }
                SDL_RenderCopy(renderer, peashooter, NULL, &pee);
                SDL_RenderPresent(renderer);
                }
            }
            */
        }

        /*
        float delta_time = (SDL_GetTicks() - last_ticks) / 1000.0f;
        last_ticks = SDL_GetTicks();
        */




        /*
        frameCounter++;
        fps_timer += delta_time;
        if(fps_timer >= 1) {
            char title[100];
            sprintf(title,"SDL project: %f FPS", frameCounter/ fps_timer);
            frameCounter = 0;
            fps_timer = 0;
            SDL_SetWindowTitle(window, title);
        }
        */
    }


    jatek_felszabadit(&uj);

    SDL_DestroyTexture(peashooter);
    //SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
