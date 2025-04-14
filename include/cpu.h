#pragma once
#include <string.h>
#include "global.h"

#define STACK_SZ 16
#define REG_CT 16
#define RAM_SIZE 4096
#define START_ADDR 0x200
#define DISPLAY_W 64
#define DISPLAY_H 32

/* This may be easier to work with if it's not being accessed via pointers,
   especially since only one struct cpu is ever initialized. */
typedef struct cpu {
    uint16_t index; /* address/index register */
    uint16_t program_ct;
    uint16_t stack[STACK_SZ]; /* 16 2-byte members is the de facto minimum size of the stack; can be expanded if needed. */
    uint8_t stack_ptr;
    uint8_t registers[REG_CT]; /* reg VY can be accessed as registers[0xY] */
    uint8_t ram[RAM_SIZE];
    uint8_t delay_timer;
    uint8_t sound_timer;
    bool display[DISPLAY_H][DISPLAY_W]; /* white if true, black otherwise */
} cpu;


cpu *init_cpu();
int load_rom(const char *filename, cpu *cpu);