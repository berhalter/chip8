#include <SDL2/SDL.h>
#include "../include/global.h"
#include "../include/cpu.h"
#include "../include/instructions.h"

#define PIXEL_SCALE 8
#define WINDOW_WIDTH (DISPLAY_W * PIXEL_SCALE)
#define WINDOW_HEIGHT (DISPLAY_H * PIXEL_SCALE)


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
        fprintf(stderr, "load_rom(\"%s\") failed.\n", argv[1]);
        free(cpu);
        cpu = NULL;
        return EXIT_FAILURE;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "ERROR: Could not initialize SDL. %s\n", SDL_GetError());
        free(cpu);
        cpu = NULL;
        return EXIT_FAILURE;
    }
    SDL_Window* window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL) {
        fprintf(stderr, "ERROR: Could not create SDL window. %s\n", SDL_GetError());
        free(cpu);
        cpu = NULL;
        return EXIT_FAILURE;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "ERROR: Could not create SDL renderer. %s\n", SDL_GetError());
        free(cpu);
        cpu = NULL;
        return EXIT_FAILURE;
    }

    bool is_running = true;
    while (is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                is_running = false;
                break;
            //this is incredibly crude, will consider fixing later
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_1:
                    cpu->is_key_pressed[0x1] = true;
                    break;
                case SDL_SCANCODE_2:
                    cpu->is_key_pressed[0x2] = true;
                    break;
                case SDL_SCANCODE_3:
                    cpu->is_key_pressed[0x3] = true;
                    break;
                case SDL_SCANCODE_4:
                    cpu->is_key_pressed[0xC] = true;
                    break;
                case SDL_SCANCODE_Q:
                    cpu->is_key_pressed[0x4] = true;
                    break;
                case SDL_SCANCODE_W:
                    cpu->is_key_pressed[0x5] = true;
                    break;
                case SDL_SCANCODE_E:
                    cpu->is_key_pressed[0x6] = true;
                    break;
                case SDL_SCANCODE_R:
                    cpu->is_key_pressed[0xD] = true;
                    break;
                case SDL_SCANCODE_A:
                    cpu->is_key_pressed[0x7] = true;
                    break;
                case SDL_SCANCODE_S:
                    cpu->is_key_pressed[0x8] = true;
                    break;
                case SDL_SCANCODE_D:
                    cpu->is_key_pressed[0x9] = true;
                    break;
                case SDL_SCANCODE_F:
                    cpu->is_key_pressed[0xE] = true;
                    break;
                case SDL_SCANCODE_Z:
                    cpu->is_key_pressed[0xA] = true;
                    break;    
                case SDL_SCANCODE_X:
                    cpu->is_key_pressed[0x0] = true;
                    break;
                case SDL_SCANCODE_C:
                    cpu->is_key_pressed[0xB] = true;
                    break;
                case SDL_SCANCODE_V:
                    cpu->is_key_pressed[0xF] = true;
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_1:
                    cpu->is_key_pressed[0x1] = false;
                    break;
                case SDL_SCANCODE_2:
                    cpu->is_key_pressed[0x2] = false;
                    break;
                case SDL_SCANCODE_3:
                    cpu->is_key_pressed[0x3] = false;
                    break;
                case SDL_SCANCODE_4:
                    cpu->is_key_pressed[0xC] = false;
                    break;
                case SDL_SCANCODE_Q:
                    cpu->is_key_pressed[0x4] = false;
                    break;
                case SDL_SCANCODE_W:
                    cpu->is_key_pressed[0x5] = false;
                    break;
                case SDL_SCANCODE_E:
                    cpu->is_key_pressed[0x6] = false;
                    break;
                case SDL_SCANCODE_R:
                    cpu->is_key_pressed[0xD] = false;
                    break;
                case SDL_SCANCODE_A:
                    cpu->is_key_pressed[0x7] = false;
                    break;
                case SDL_SCANCODE_S:
                    cpu->is_key_pressed[0x8] = false;
                    break;
                case SDL_SCANCODE_D:
                    cpu->is_key_pressed[0x9] = false;
                    break;
                case SDL_SCANCODE_F:
                    cpu->is_key_pressed[0xE] = false;
                    break;
                case SDL_SCANCODE_Z:
                    cpu->is_key_pressed[0xA] = false;
                    break;    
                case SDL_SCANCODE_X:
                    cpu->is_key_pressed[0x0] = false;
                    break;
                case SDL_SCANCODE_C:
                    cpu->is_key_pressed[0xB] = false;
                    break;
                case SDL_SCANCODE_V:
                    cpu->is_key_pressed[0xF] = false;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        uint16_t opcode = fetch_instruction(cpu);
        if (decode_instruction(cpu, opcode) != 0) {
            fprintf(stderr, "decode_instruction(0x%x) failed.\n", opcode);
        }
        

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        /* Try to find a way to scale this without so much nesting (use rects?) */
        for (int y = 0; y < DISPLAY_H; ++y) {
            for (int x = 0; x < DISPLAY_W; ++x) {
                for (int sy = 0; sy < PIXEL_SCALE; ++sy) {
                    for (int sx = 0; sx < PIXEL_SCALE; ++sx) {
                        if (cpu->display[y][x] == 1) {
                            SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);
                            SDL_RenderDrawPoint(renderer, (x*PIXEL_SCALE)+sx, (y*PIXEL_SCALE)+sy);
                        } else {
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderDrawPoint(renderer, (x*PIXEL_SCALE)+sx, (y*PIXEL_SCALE)+sy);
                        }
                    }
                }
                    
            }
            
        }
        SDL_RenderPresent(renderer);
    }
    free(cpu);
    cpu = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



    return EXIT_SUCCESS;
}
