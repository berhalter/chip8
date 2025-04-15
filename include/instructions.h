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

/* Execute machine language subroutine at address NNN */
void op_0NNN(uint16_t address);

/* Clear the screen */
void op_00E0(cpu_t *cpu);

/* Return from a subroutine */
void op_00EE(cpu_t *cpu);

/* Jump to address NNN */
void op_1NNN(cpu_t *cpu, uint16_t address);

/* Execute subroutine starting at address NNN */
void op_2NNN(cpu_t *cpu, uint16_t address);

/* Skip the following instruction if the value of register VX equals NN  */
void op_3XNN(cpu_t *cpu, uint8_t vx, uint8_t nnval);

/* Skip the following instruction if the value of register VX is not equal to NN */
void op_4XNN(cpu_t *cpu, uint8_t vx, uint8_t nnval);

/* Skip the following instruction if the value of register VX is equal to the value of register VY */
void op_5XY0(cpu_t *cpu, uint8_t vx, uint8_t vy);

/* Store number NN in register VX */
void op_6XNN(cpu_t *cpu, uint8_t vx, uint8_t nnval);

/* Add the value NN to register VX */
void op_7XNN(cpu_t *cpu, uint8_t vx, uint8_t nnval);

/* Store the value of register VY in register VX */
void op_8XY0(cpu_t *cpu, uint8_t vx, uint8_t vy);

/* Set VX to VX OR VY */
void op_8XY1(cpu_t *cpu, uint8_t vx, uint8_t vy);

/* Set VX to VX AND VY */
void op_8XY2(cpu_t *cpu, uint8_t vx, uint8_t vy);

/* Set VX to VX XOR VY */
void op_8XY3(cpu_t *cpu, uint8_t vx, uint8_t vy);

/* Add the value of register VY to register VX
   Set VF to 01 if a carry occurs
   Set VF to 00 if a carry does not occur */
void op_8XY4(cpu_t *cpu, uint8_t vx, uint8_t vy);

/* Subtract the value of register VY from register VX
   Set VF to 00 if a borrow occurs
   Set VF to 01 if a borrow does not occur */
void op_8XY5(cpu_t *cpu, uint8_t vx, uint8_t vy);

/* Store the value of register VY shifted right one bit in register VX
   Set register VF to the least significant bit prior to the shift
   VY is unchanged */
void op_8XY6(cpu_t *cpu, uint8_t vx, uint8_t vy);

/* Set register VX to the value of VY minus VX
   Set VF to 00 if a borrow occurs
   Set VF to 01 if a borrow does not occur*/
void op_8XY7(cpu_t *cpu, uint8_t vx, uint8_t vy);

/* Store the value of register VY shifted left one bit in register VX
   Set register VF to the most significant bit prior to the shift
   VY is unchanged*/
void op_8XYE(cpu_t *cpu, uint8_t vx, uint8_t vy);

/* Skip the following instruction if the value of register VX is not equal to the value of register VY */
void op_9XY0(cpu_t *cpu, uint8_t vx, uint8_t vy);

/* Store memory address NNN in register I */
void op_ANNN(cpu_t *cpu, uint16_t address);

/* Jump to address NNN + V0 */
void op_BNNN(cpu_t *cpu, uint16_t address);

/* Set VX to a random number with a mask of NN */
void op_CXNN(cpu_t *cpu, uint8_t vx, uint8_t nnval);

/* Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
   Set VF to 01 if any set pixels are changed to unset, and 00 otherwise */
void op_DXYN(cpu_t *cpu, uint8_t vx, uint8_t vy, uint8_t nval);

/* Skip the following instruction if the key corresponding to the hex value currently stored in register VX is pressed */
void op_EX9E(cpu_t *cpu, uint8_t vx);

/* Skip the following instruction if the key corresponding to the hex value currently stored in register VX is not pressed */
void op_EXA1(cpu_t *cpu, uint8_t vx);

/* Store the current value of the delay timer in register VX */
void op_FX07(cpu_t *cpu, uint8_t vx);

/* Wait for a keypress and store the result in register VX */
void op_FX0A(cpu_t *cpu, uint8_t vx);

/* Set the delay timer to the value of register VX */
void op_FX15(cpu_t *cpu, uint8_t vx);

/* Set the sound timer to the value of register VX */
void op_FX18(cpu_t *cpu, uint8_t vx);

/* Add the value stored in register VX to register I */
void op_FX1E(cpu_t *cpu, uint8_t vx);

/* Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX */
void op_FX29(cpu_t *cpu, uint8_t vx);

/* Store the binary-coded decimal equivalent of the value stored in register VX at addresses I, I + 1, and I + 2 */
void op_FX33(cpu_t *cpu, uint8_t vx);

/* Store the values of registers V0 to VX inclusive in memory starting at address I
   I is set to I + X + 1 after operation */
void op_FX55(cpu_t *cpu, uint8_t vx);

/* Fill registers V0 to VX inclusive with the values stored in memory starting at address I
   I is set to I + X + 1 after operation */
void op_FX65(cpu_t *cpu, uint8_t vx);