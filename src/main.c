#include <SDL2/SDL.h>
#include "../include/global.h"
#include "../include/cpu.h"
#include "../include/instructions.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define PIXEL_SCALE 8

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Missing arguments. Usage: chip8 file\n");
        return EXIT_FAILURE;
    }
    //printf("ROM file: %s\n", argv[1]);

    /* Consider creating setup functions for readability */

    cpu_t *cpu = init_cpu();
    if (cpu == NULL) {
        /* No need to free cpu here since allocation failed. */
        fprintf(stderr, "init_cpu() failed.\n");
        return EXIT_FAILURE;
    }

    if (load_rom(argv[1], cpu) != 0) {
        fprintf(stderr, "load_rom() failed.\n");
        return EXIT_FAILURE;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "ERROR: Could not initialize SDL. %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL) {
        fprintf(stderr, "ERROR: Could not create SDL window. %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "ERROR: Could not create SDL renderer. %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    bool is_running = true;
    while (is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                op_00E0(cpu);
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        /* Try to find a way to scale this without so much nesting */
        for (int y = 0; y < DISPLAY_H; ++y) {
            for (int x = 0; x < DISPLAY_W; ++x) {
                for (int sy = 0; sy < PIXEL_SCALE; ++sy) {
                    for (int sx = 0; sx < PIXEL_SCALE; ++sx) {
                        if (cpu->display[y][x]) {
                            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                            SDL_RenderDrawPoint(renderer, (x*PIXEL_SCALE)+sx, (y*PIXEL_SCALE)+sy);
                        } else {
                            SDL_SetRenderDrawColor(renderer, 0, 64, 0, 255);
                            SDL_RenderDrawPoint(renderer, (x*PIXEL_SCALE)+sx, (y*PIXEL_SCALE)+sy);
                        }
                    }
                }
                    
            }
            
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



    return EXIT_SUCCESS;
}
