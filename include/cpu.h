#pragma once
#include "global.h"

//remove typedef for clarity?
typedef struct cpu {
    uint16_t index; /* address/index register */
    uint16_t program_ct;
    uint16_t stack[16]; /* 16 2-byte members is the de facto minimum size of the stack; can be expanded if needed. */
    uint8_t stack_ptr;
    uint8_t registers[16]; /* reg VY can be accessed as registers[0xY] */
    uint8_t ram[4096];
    uint8_t delay_timer;
    uint8_t sound_timer;
} cpu;


cpu *init_cpu();
void load_rom();
void fetch();
void decode();