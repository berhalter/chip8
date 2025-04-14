#include "../include/global.h"
#include "../include/cpu.h"
#include "../include/instructions.h"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Missing arguments. Usage: chip8 file\n");
        return EXIT_FAILURE;
    }
    printf("ROM file: %s\n", argv[1]);
    cpu *cpu = init_cpu();
    if (cpu == NULL) {
        /* No need to free cpu here since allocation failed. */
        fprintf(stderr, "init_cpu() failed.\n");
        return EXIT_FAILURE;
    }
    if (load_rom(argv[1], cpu) != 0) {
        fprintf(stderr, "load_rom() failed.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
