#include "../include/cpu.h"

cpu_t *init_cpu() {
    /* TO-DO: 
     * specify when cpu should be freed by the program. */
    cpu_t *cpu;
    cpu = calloc(1, sizeof(*cpu)); /* barring the program counter and font data, it's best if every cpu member starts at 0. */
    if (cpu == NULL) {
        perror("ERROR: Could not initialize CPU.\n");
        return NULL;
    }
    cpu->program_ct = START_ADDR;
    if (set_font(cpu) != 0) {
        fprintf(stderr, "set_font() failed.\n");
        return NULL;
    }
    //for debugging using 5-quirks.ch8 and 6-keypad.ch8:
    cpu->ram[0x1FF] = 1;
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

/* Places font data in memory and stores the address where each sprite is
   located in cpu->font_addr[], where each hexadecimal index of font_addr
   corresponds to a sprite in the font (e.g., Sprite data for the character
   'A' is begins at the memory address stored in font_addr[0xA])). */
int set_font(cpu_t *cpu) {
    uint8_t font[] = {0xF0, 0x90, 0x90, 0x90, 0xF0,      // 0
                      0x20, 0x60, 0x20, 0x20, 0x70,      // 1
                      0xF0, 0x10, 0xF0, 0x80, 0xF0,      // 2
                      0xF0, 0x10, 0xF0, 0x10, 0xF0,      // 3
                      0x90, 0x90, 0xF0, 0x10, 0x10,      // 4
                      0xF0, 0x80, 0xF0, 0x10, 0xF0,      // 5
                      0xF0, 0x80, 0xF0, 0x90, 0xF0,      // 6
                      0xF0, 0x10, 0x20, 0x40, 0x40,      // 7
                      0xF0, 0x90, 0xF0, 0x90, 0xF0,      // 8
                      0xF0, 0x90, 0xF0, 0x10, 0xF0,      // 9
                      0xF0, 0x90, 0xF0, 0x90, 0x90,      // A
                      0xE0, 0x90, 0xE0, 0x90, 0xE0,      // B
                      0xF0, 0x80, 0x80, 0x80, 0xF0,      // C
                      0xE0, 0x90, 0x90, 0x90, 0xE0,      // D
                      0xF0, 0x80, 0xF0, 0x80, 0xF0,      // E
                      0xF0, 0x80, 0xF0, 0x80, 0x80};     // F
    int sprite_size = 5;
    for (int i = 0; i < KEY_COUNT; ++i) {
        uint16_t address = i * sprite_size;
        cpu->font_addr[i] = address;
        memcpy(&(cpu->ram[address]), &font[address], sprite_size);
    }
    return 0;
}

void decrement_timers(cpu_t *cpu) {
    if (cpu->delay_timer > 0) {
        --(cpu->delay_timer);
    }
    if (cpu->sound_timer > 0) {
        --(cpu->sound_timer);
    }
}