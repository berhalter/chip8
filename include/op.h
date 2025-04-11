#include "global.h"
//It might make sense to merge this file with cpu.h for scope reasons.

/* TODO:
format this so that it's easier to read.
*/

/* KEY:
 * NNN == Hexadecimal memory address
 * NN  == Hexadecimal byte
 * N   == Hexadecimal nibble
 * X/Y == Register(s)
*/

void op_0NNN(uint16_t address); /* Execute machine language subroutine at address NNN */
void op_00E0(); /* Clear the screen */
void op_00EE(); /* Return from a subroutine */
void op_1NNN(uint16_t address); /* Jump to address NNN */
void op_2NNN(uint16_t address); /* Execute subroutine starting at address NNN */
void op_3XNN(uint8_t vx, uint8_t nnval); /* Skip the following instruction if the value of register VX equals NN  */
void op_4XNN(uint8_t vx, uint8_t nnval); /* Skip the following instruction if the value of register VX is not equal to NN */
void op_5XY0(uint8_t vx, uint8_t vy); /* Skip the following instruction if the value of register VX is equal to the value of register VY */
void op_6XNN(uint8_t vx, uint8_t nnval); /* Store number NN in register VX */
void op_7XNN(uint8_t vx, uint8_t nnval); /* Add the value NN to register VX */
void op_8XY0(); /* Store the value of register VY in register VX */
void op_8XY1(uint8_t vx, uint8_t vy); /* Set VX to VX OR VY */
void op_8XY2(uint8_t vx, uint8_t vy); /* Set VX to VX AND VY */
void op_8XY3(uint8_t vx, uint8_t vy); /* Set VX to VX XOR VY */
void op_8XY4(uint8_t vx, uint8_t vy); /* Add the value of register VY to register VX
                                           Set VF to 01 if a carry occurs
                                           Set VF to 00 if a carry does not occur*/
void op_8XY5(uint8_t vx, uint8_t vy); /* Subtract the value of register VY from register VX
                                           Set VF to 00 if a borrow occurs
                                           Set VF to 01 if a borrow does not occur*/
void op_8XY6(uint8_t vx, uint8_t vy); /* Store the value of register VY shifted right one bit in register VX
                                           Set register VF to the least significant bit prior to the shift
                                           VY is unchanged */
void op_8XY7(uint8_t vx, uint8_t vy); /* Set register VX to the value of VY minus VX
                                           Set VF to 00 if a borrow occurs
                                           Set VF to 01 if a borrow does not occur*/
void op_8XYE(uint8_t vx, uint8_t vy); /* Store the value of register VY shifted left one bit in register VX
                                           Set register VF to the most significant bit prior to the shift
                                           VY is unchanged*/
void op_9XY0(uint8_t vx, uint8_t vy); /* Skip the following instruction if the value of register VX is not equal to the value of register VY */
void op_ANNN(uint16_t address); /* Store memory address NNN in register I */
void op_BNNN(uint16_t address); /* Jump to address NNN + V0 */
void op_CXNN(uint8_t vx, uint8_t nnval); /* Set VX to a random number with a mask of NN */
void op_DXYN(uint8_t vx, uint8_t vy, uint8_t nval); /* Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
                                         Set VF to 01 if any set pixels are changed to unset, and 00 otherwise */
void op_EX9E(uint8_t vx); /* Skip the following instruction if the key corresponding to the hex value currently stored in register VX is pressed */
void op_EXA1(uint8_t vx); /* Skip the following instruction if the key corresponding to the hex value currently stored in register VX is not pressed */
void op_FX07(uint8_t vx); /* Store the current value of the delay timer in register VX */
void op_FX0A(uint8_t vx); /* Wait for a keypress and store the result in register VX */
void op_FX15(uint8_t vx); /* Set the delay timer to the value of register VX */
void op_FX18(uint8_t vx); /* Set the sound timer to the value of register VX */
void op_FX1E(uint8_t vx); /* Add the value stored in register VX to register I */
void op_FX29(uint8_t vx); /* Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX */
void op_FX33(uint8_t vx); /* Store the binary-coded decimal equivalent of the value stored in register VX at addresses I, I + 1, and I + 2 */
void op_FX55(uint8_t vx); /* Store the values of registers V0 to VX inclusive in memory starting at address I
                             I is set to I + X + 1 after operation */
void op_FX65(uint8_t vx); /* Fill registers V0 to VX inclusive with the values stored in memory starting at address I
                             I is set to I + X + 1 after operation */