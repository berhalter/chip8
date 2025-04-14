#include "../include/cpu.h"

/* REWRITE SO THAT PROGRAM ONLY EXITS FROM MAIN FUNCTION */

cpu *init_cpu() {
    /* TO-DO: specify when cpu should be freed by the program. */
    cpu *cpu;
    cpu = calloc(1, sizeof(*cpu));
    if (cpu == NULL) {
        perror("ERROR: Could not initialize CPU.\n");
        return NULL;
    }
    cpu->program_ct = START_ADDR;
    return cpu;
}

int load_rom(const char *filename, cpu *cpu) {
    FILE *rom = fopen(filename, "r");
    if (rom == NULL) {
        perror("ERROR: Could not open ROM file.\n");
        return 1;
    }
    if (fseek(rom, 0L, SEEK_END) != 0) {
        perror("ERROR: Could not obtain ROM file size.\n");
        return 2;
    }
    long size = ftell(rom);
    if (size == 0) {
        fprintf(stderr, "ERROR: ROM file is empty (0B).\n");
        return 3;
    } else if (size > RAM_SIZE) {
        fprintf(stderr, "ERROR: ROM file is too large (>4096B).\n");
        return 4;
    }
    rewind(rom);
    memcpy((cpu->ram + START_ADDR), rom, size);
    if (fclose(rom) != 0) {
        perror("ERROR: Could not close ROM file.\n");
        return 5;
    }
    return 0;
}

void fetch() {
    return;
}

void decode() {
    return;
}