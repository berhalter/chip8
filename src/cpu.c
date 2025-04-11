#include "../include/cpu.h"

cpu *init_cpu() {
    /* TO-DO: specify when cpu should be freed by the program. */
    cpu *cpu;
    cpu = calloc(1, sizeof(*cpu));
    if (cpu == NULL) {
        fprintf(stderr, "ERROR: Could not initialize CPU.");
        exit(EXIT_FAILURE);
    }
    return cpu;
}

void load_rom() {
    return;
}

void fetch() {
    return;
}

void decode() {
    return;
}