#pragma once
#include <string.h>
#include "global.h"

#define STACK_SZ 16
#define REG_CT 16
#define RAM_SIZE 4096
#define START_ADDR 0x200
#define DISPLAY_W 64
#define DISPLAY_H 32
#define KEY_COUNT 16

typedef struct cpu {
    uint16_t index; /* index register, used by some instructions to store addresses */
    uint16_t program_ct;
    uint16_t stack[STACK_SZ]; /* 16 2-byte members is the de facto minimum size of the stack; can be expanded if needed. */
    uint8_t stack_ptr;
    uint8_t registers[REG_CT]; /* reg VY can be accessed as registers[0xY] */
    uint8_t ram[RAM_SIZE];
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t display[DISPLAY_H][DISPLAY_W]; /* on = 1, off = 0 */
    uint8_t font_addr[KEY_COUNT]; /* makes op_FX29 less annoying, see set_font() implementation in cpu.c for details */
    bool is_key_pressed[KEY_COUNT];
} cpu_t;

cpu_t *init_cpu();
int load_rom(const char *filename, cpu_t *cpu);
int set_font(cpu_t *cpu);