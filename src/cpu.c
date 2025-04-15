#include "../include/cpu.h"

cpu_t *init_cpu() {
    /* TO-DO: 
     * specify when cpu should be freed by the program. */
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
    if (cpu == NULL) {
        fprintf(stderr, "ERROR: NULL cpu pointer was passed to load_rom().\n");
        return 1;
    }
    /* From `man 3 fopen`:
       "(Other systems may treat text files and binary files differently, and
       adding the 'b' may be a good idea if you do I/O to a binary file and
       expect that your program may be ported to non-UNIX environments.)" */
    FILE *rom = fopen(filename, "rb");
    if (rom == NULL) {
        perror("ERROR: Could not open ROM file.\n");
        fprintf(stderr, "Filename: %s\n", filename);
        return 2;
    }
    if (fseek(rom, 0L, SEEK_END) != 0) {
        perror("ERROR: Could not obtain ROM file size.\n");
        return 3;
    }
    long size = ftell(rom);
    /* max_size is inaccurate due to the uppermost bytes being reserved on
       older 4K systems, but I'm unsure as to how much this actually matters.
       https://en.wikipedia.org/wiki/CHIP-8#Memory */
    long max_size = RAM_SIZE - START_ADDR;
    if (size == 0) {
        fprintf(stderr, "ERROR: ROM file is empty (%ldB).\n", size);
        return 4;
    } else if (size > max_size) {
        fprintf(stderr, "ERROR: ROM file is too large (%ldB > %ldB).\n", size, max_size);
        return 5;
    }
    rewind(rom);
    for (long i = 0; i < size; ++i) {
        cpu->ram[START_ADDR + i] = fgetc(rom);
    }
    if (fclose(rom) != 0) {
        perror("ERROR: Could not close ROM file.\n");
        return 6;
    }
    return 0;
}
