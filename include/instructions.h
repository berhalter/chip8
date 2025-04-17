#pragma once
#include "global.h"
#include "../include/cpu.h"

uint16_t fetch_instruction(cpu_t *cpu);
int decode_instruction(cpu_t *cpu, uint16_t opcode);

/* OPCODES KEY:
 * NNN == Hexadecimal memory address
 * NN  == Hexadecimal byte
 * N   == Hexadecimal nibble
 * X/Y == Register(s)
*/

/* As much as I would rather name these functions based on what they do,
   keeping the original 4-character opcode names should help prevent errors
   when decoding instructions, since it will be visually obvious if the wrong
   function is called inside the switch statement. */
void op_0NNN(uint16_t address);
void op_00E0(cpu_t *cpu);
void op_00EE(cpu_t *cpu);
void op_1NNN(cpu_t *cpu, uint16_t address);
void op_2NNN(cpu_t *cpu, uint16_t address);
void op_3XNN(cpu_t *cpu, uint8_t vx, uint8_t nnval);
void op_4XNN(cpu_t *cpu, uint8_t vx, uint8_t nnval);
void op_5XY0(cpu_t *cpu, uint8_t vx, uint8_t vy);
void op_6XNN(cpu_t *cpu, uint8_t vx, uint8_t nnval);
void op_7XNN(cpu_t *cpu, uint8_t vx, uint8_t nnval);
void op_8XY0(cpu_t *cpu, uint8_t vx, uint8_t vy);
void op_8XY1(cpu_t *cpu, uint8_t vx, uint8_t vy);
void op_8XY2(cpu_t *cpu, uint8_t vx, uint8_t vy);
void op_8XY3(cpu_t *cpu, uint8_t vx, uint8_t vy);
void op_8XY4(cpu_t *cpu, uint8_t vx, uint8_t vy);
void op_8XY5(cpu_t *cpu, uint8_t vx, uint8_t vy);
void op_8XY6(cpu_t *cpu, uint8_t vx, uint8_t vy);
void op_8XY7(cpu_t *cpu, uint8_t vx, uint8_t vy);
void op_8XYE(cpu_t *cpu, uint8_t vx, uint8_t vy);
void op_9XY0(cpu_t *cpu, uint8_t vx, uint8_t vy);
void op_ANNN(cpu_t *cpu, uint16_t address);
void op_BNNN(cpu_t *cpu, uint16_t address);
void op_CXNN(cpu_t *cpu, uint8_t vx, uint8_t nnval);
void op_DXYN(cpu_t *cpu, uint8_t vx, uint8_t vy, uint8_t nval);
void op_EX9E(cpu_t *cpu, uint8_t vx);
void op_EXA1(cpu_t *cpu, uint8_t vx);
void op_FX07(cpu_t *cpu, uint8_t vx);
void op_FX0A(cpu_t *cpu, uint8_t vx);
void op_FX15(cpu_t *cpu, uint8_t vx);
void op_FX18(cpu_t *cpu, uint8_t vx);
void op_FX1E(cpu_t *cpu, uint8_t vx);
void op_FX29(cpu_t *cpu, uint8_t vx);
void op_FX33(cpu_t *cpu, uint8_t vx);
void op_FX55(cpu_t *cpu, uint8_t vx);
void op_FX65(cpu_t *cpu, uint8_t vx);