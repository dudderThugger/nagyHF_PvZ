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
void draw_peashooters(SDL_Renderer * renderer, Rects** palya, Peashooter_list* peashooter_list){
    SDL_Texture *texture = IMG_LoadTexture(renderer, "peashooter.png");
    Peashooter* iter = peashooter_list->first;
    while(iter != NULL) {
        SDL_Rect rect= {.x = palya[iter->pozicio.x][iter->pozicio.y].x,
                    .y = palya[iter->pozicio.x][iter->pozicio.y].y,
                    .h = palya[iter->pozicio.x][iter->pozicio.y].h,
                    .w = palya[iter->pozicio.x][iter->pozicio.y].w};
        SDL_RenderCopy(renderer,texture,NULL,&rect);
    }
    SDL_DestroyTexture(texture);
}
/**
 *@brief Az összes sunflower kirajzolását végző függvény
 *
 *@param renderer A rendererre mutató pointer
 *@param palya A palya téglalapjaira mutató, pointerek tömbje, amiből az adatokat szedjük a képek beillesztéséhez
 *@param sunflower_din a sunflowerek dinamikus tömbje
 */
void draw_sunflowers(SDL_Renderer * renderer, Rects** palya, Sunflower_list* sunflower_list){
    SDL_Texture *texture = IMG_LoadTexture(renderer, "sunflower.png");
    Sunflower* iter = sunflower_list->first;
    while(iter != NULL) {
        SDL_Rect rect= {.x = palya[iter->pozicio.x][iter->pozicio.y].x,
                    .y = palya[iter->pozicio.x][iter->pozicio.y].y,
                    .h = palya[iter->pozicio.x][iter->pozicio.y].h,
                    .w = palya[iter->pozicio.x][iter->pozicio.y].w};
        SDL_RenderCopy(renderer,texture,NULL,&rect);
    }
    SDL_DestroyTexture(texture);
}
/**
 *@brief Az összes wallnut kirajzolását végző függvény
 *
 *@param renderer A rendererre mutató pointer
 *@param palya A palya téglalapjaira mutató, pointerek tömbje, amiből az adatokat szedjük a képek beillesztéséhez
 *@param wallnut_din a wallnutok dinamikus tömbje
 */
void draw_wallnuts(SDL_Renderer * renderer, Rects** palya, Wallnut_list* wallnut_list){
    SDL_Texture *texture = IMG_LoadTexture(renderer, "wallnut.png");
    Wallnut* iter = wallnut_list->first;
    while(iter != NULL) {
        SDL_Rect rect= {.x = palya[iter->pozicio.x][iter->pozicio.y].x,
                    .y = palya[iter->pozicio.x][iter->pozicio.y].y,
                    .h = palya[iter->pozicio.x][iter->pozicio.y].h,
                    .w = palya[iter->pozicio.x][iter->pozicio.y].w};
        SDL_RenderCopy(renderer,texture,NULL,&rect);
    }
    SDL_DestroyTexture(texture);
}
/**
 *@brief Az összes zombi kirajzolását végző függvény
 *
 *@param renderer A rendererre mutató pointer
 *@param palya A palya téglalapjaira mutató, pointerek tömbje, amiből az adatokat szedjük a képek beillesztéséhez
 *@param zombies_din A zombik dinamikus tömbje
 */
void draw_zombies(SDL_Renderer * renderer, Rects** palya, Zombie_list* zombie_list){
    SDL_Texture *texture = IMG_LoadTexture(renderer, "zombie.png");
    Zombi* iter = zombie_list->first;
    while(iter != NULL) {
        SDL_Rect rect= {.x = iter->pozicio.x,
                        .y = palya[iter->pozicio.x][iter->pozicio.y].y,
                        .h = palya[0][iter->pozicio.y].h,
                        .w = palya[0][iter->pozicio.y].w};
        SDL_RenderCopy(renderer,texture,NULL,&rect);
    }
    SDL_DestroyTexture(texture);
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
SDL_Rect get_rect(Rects** palya, int sor, int oszlop, int width, int height, Pont* selected) {
    SDL_Rect rect;
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x,&mouse_y);
    rect.h = palya[mouse_x/(width/oszlop)][(mouse_y-60)/(height/sor)].h;
    rect.y = palya[mouse_x/(width/oszlop)][(mouse_y-60)/(height/sor)].y;
    rect.x = palya[mouse_x/(width/oszlop)][(mouse_y-60)/(height/sor)].x;
    rect.w = palya[mouse_x/(width/oszlop)][(mouse_y-60)/(height/sor)].w;
    return rect;
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
/**
 *@brief A lövedékek kirajzolását végző függvény
 *
 * A lövedék poziciójának x koordinátája megadja a kör x koordinátáját, az y pedig, hogy melyik sorban legyen
 *@param renderer A rendererre mutató pointer
 *@param lovedekek_din A övedékek dinamikus pointere
 *@param magas
 */
void draw_bullets(SDL_Renderer* renderer, Lovedek_list* lovedekek_list, int magas){
    int x, y;
    Lovedek* iter = lovedekek_list->first;
    while(iter != NULL) {
        x = iter->pozicio.x;
        y = (magas/2)+magas * iter->pozicio.y + 40;
        filledCircleRGBA(renderer, x, y, 10, 230, 255, 0, 255);
        circleRGBA(renderer, x, y, 10, 0, 0, 0, 255);
        iter = iter->next;
    }
}