#include "../include/cpu.h"

cpu_t *init_cpu() {
    /* TO-DO: 
     * specify when cpu should be freed by the program.
     * set initial value of display for debugging.*/
    cpu_t *cpu;
    cpu = calloc(1, sizeof(*cpu));
    if (cpu == NULL) {
        perror("ERROR: Could not initialize CPU.\n");
        return NULL;
    }
    cpu->program_ct = START_ADDR;
    return cpu;
}

int load_rom(const char *filename, cpu_t *cpu) {
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
    /* max_size is inaccurate due to the uppermost bytes being reserved on
       older 4K systems, but I'm unsure as to how much this actually matters.
       https://en.wikipedia.org/wiki/CHIP-8#Memory */
    long max_size = RAM_SIZE - START_ADDR;
    if (size == 0) {
        fprintf(stderr, "ERROR: ROM file is empty (0B).\n");
        return 3;
    } else if (size > max_size) {
        fprintf(stderr, "ERROR: ROM file is too large (>%ld).\n", max_size);
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
