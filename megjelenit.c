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


void draw_background(SDL_Renderer *renderer, Rects** palya, int const sor, int const oszlop) {
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
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
}
