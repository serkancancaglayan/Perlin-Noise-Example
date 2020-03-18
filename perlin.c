#include "noise.h"
#include <SDL2/SDL.h>
#define WindowWidth 800
#define WindowHeight 600
int main(){
     if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Window * window;
        SDL_Renderer * renderer;
        SDL_Event event;
        SDL_bool done = SDL_FALSE;
        if(!SDL_CreateWindowAndRenderer(WindowWidth, WindowHeight, 0, &window, &renderer)){
            SDL_SetWindowTitle(window, "Perlin");
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_TRANSPARENT);
            SDL_RenderClear(renderer);
            for(int i = 0; i < WindowWidth; i++){
                for(int j = 0; j < WindowHeight; j++){
                    int gray_scale = (int)(perlin2d(i, j, 0.008, 12) * 256);
                    SDL_SetRenderDrawColor(renderer, gray_scale, gray_scale, gray_scale, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawPoint(renderer, i, j);
                }
            }
            SDL_RenderPresent(renderer);
            while(!done){
                SDL_PollEvent(&event);
                if(event.type == SDL_QUIT){
                    done = SDL_TRUE;
                }
            }
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            SDL_Quit();
        }else{
            fprintf(stderr, "Failed to create window or renderer : %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    }else{
        fprintf(stderr, "Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}