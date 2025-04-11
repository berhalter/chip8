#include "global.h"


/* consider using just an array for this;
   it may make decoding easier since the X and Y values of instructions
   can be passed in as (hex) indices. */
typedef struct registers {
    /* All VX registers are general purpose, EXCEPT for VF, which is often used for flags */
    uint8_t V0;
    uint8_t V1;
    uint8_t V2;
    uint8_t V3;
    uint8_t V4;
    uint8_t V5;
    uint8_t V6;
    uint8_t V7;
    uint8_t V8;
    uint8_t V9;
    uint8_t VA;
    uint8_t VB;
    uint8_t VC;
    uint8_t VD;
    uint8_t VE;
    uint8_t VF;
} registers;


typedef struct cpu {
    registers *regs;
    uint16_t index; /* address/index register */
    uint16_t pc;
    uint16_t stack[16]; /* 16 2-byte members is the de facto minimum size of the stack; can be expanded if needed. */
    uint8_t ram[4096];
    uint8_t delay_timer;
    uint8_t sound_timer;
} cpu;


cpu *init_cpu();
void load_rom();
void fetch();
void decode();