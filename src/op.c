#include "../include/op.h"

/* Execute machine language subroutine at address NNN */
void op_0NNN(uint16_t address) {
    printf("Not implemented.");
    return;
}

/* Clear the screen */
void op_00E0() {
    printf("Not implemented.");
    return;
}

/* Return from a subroutine */
void op_00EE() {
    printf("Not implemented.");
    return;
}

/* Jump to address NNN */
void op_1NNN(uint16_t address) {
    printf("Not implemented.");
    return;
}

/* Execute subroutine starting at address NNN */
void op_2NNN(uint16_t address) {
    printf("Not implemented.");
    return;
}

/* Skip the following instruction if the value of register VX equals NN  */
void op_3XNN(uint8_t vx, uint8_t nnval) {
    printf("Not implemented.");
    return;
}

/* Skip the following instruction if the value of register VX is not equal to NN */
void op_4XNN(uint8_t vx, uint8_t nnval) {
    printf("Not implemented.");
    return;
}

/* Skip the following instruction if the value of register VX is equal to the value of register VY */
void op_5XY0(uint8_t vx, uint8_t vy) {
    printf("Not implemented.");
    return;
}

/* Store number NN in register VX */
void op_6XNN(uint8_t vx, uint8_t nnval) {
    printf("Not implemented.");
    return;
}

/* Add the value NN to register VX */
void op_7XNN(uint8_t vx, uint8_t nnval) {
    printf("Not implemented.");
    return;
}

/* Store the value of register VY in register VX */
void op_8XY0(uint8_t vx, uint8_t vy) {
    printf("Not implemented.");
    return;
}

/* Set VX to VX OR VY */
void op_8XY1(uint8_t vx, uint8_t vy) {
    printf("Not implemented.");
    return;
}

/* Set VX to VX AND VY */
void op_8XY2(uint8_t vx, uint8_t vy) {
    printf("Not implemented.");
    return;
}

/* Set VX to VX XOR VY */
void op_8XY3(uint8_t vx, uint8_t vy) {
    printf("Not implemented.");
    return;
}

/* Add the value of register VY to register VX
   Set VF to 01 if a carry occurs
   Set VF to 00 if a carry does not occur */
void op_8XY4(uint8_t vx, uint8_t vy) {
    printf("Not implemented.");
    return;
}

/* Subtract the value of register VY from register VX
   Set VF to 00 if a borrow occurs
   Set VF to 01 if a borrow does not occur */
void op_8XY5(uint8_t vx, uint8_t vy) {
    printf("Not implemented.");
    return;
}

/* Store the value of register VY shifted right one bit in register VX
   Set register VF to the least significant bit prior to the shift
   VY is unchanged */
void op_8XY6(uint8_t vx, uint8_t vy) {
    printf("Not implemented.");
    return;
}

/* Set register VX to the value of VY minus VX
   Set VF to 00 if a borrow occurs
   Set VF to 01 if a borrow does not occur*/
void op_8XY7(uint8_t vx, uint8_t vy) {
    printf("Not implemented.");
    return;
}

/* Store the value of register VY shifted left one bit in register VX
   Set register VF to the most significant bit prior to the shift
   VY is unchanged*/
void op_8XYE(uint8_t vx, uint8_t vy) {
    printf("Not implemented.");
    return;
}

/* Skip the following instruction if the value of register VX is not equal to the value of register VY */
void op_9XY0(uint8_t vx, uint8_t vy) {
    printf("Not implemented.");
    return;
}

/* Store memory address NNN in register I */
void op_ANNN(uint16_t address) {
    printf("Not implemented.");
    return;
}

/* Jump to address NNN + V0 */
void op_BNNN(uint16_t address) {
    printf("Not implemented.");
    return;
}

/* Set VX to a random number with a mask of NN */
void op_CXNN(uint8_t vx, uint8_t nnval) {
    printf("Not implemented.");
    return;
}

/* Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
   Set VF to 01 if any set pixels are changed to unset, and 00 otherwise */
void op_DXYN(uint8_t vx, uint8_t vy, uint8_t nval) {
    printf("Not implemented.");
    return;
}

/* Skip the following instruction if the key corresponding to the hex value currently stored in register VX is pressed */
void op_EX9E(uint8_t vx) {
    printf("Not implemented.");
    return;
}

/* Skip the following instruction if the key corresponding to the hex value currently stored in register VX is not pressed */
void op_EXA1(uint8_t vx) {
    printf("Not implemented.");
    return;
}

/* Store the current value of the delay timer in register VX */
void op_FX07(uint8_t vx) {
    printf("Not implemented.");
    return;
}

/* Wait for a keypress and store the result in register VX */
void op_FX0A(uint8_t vx) {
    printf("Not implemented.");
    return;
}

/* Set the delay timer to the value of register VX */
void op_FX15(uint8_t vx) {
    printf("Not implemented.");
    return;
}

/* Set the sound timer to the value of register VX */
void op_FX18(uint8_t vx) {
    printf("Not implemented.");
    return;
}

/* Add the value stored in register VX to register I */
void op_FX1E(uint8_t vx) {
    printf("Not implemented.");
    return;
}

/* Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX */
void op_FX29(uint8_t vx) {
    printf("Not implemented.");
    return;
}

/* Store the binary-coded decimal equivalent of the value stored in register VX at addresses I, I + 1, and I + 2 */
void op_FX33(uint8_t vx) {
    printf("Not implemented.");
    return;
}

/* Store the values of registers V0 to VX inclusive in memory starting at address I
   I is set to I + X + 1 after operation */
void op_FX55(uint8_t vx) {
    printf("Not implemented.");
    return;
}

/* Fill registers V0 to VX inclusive with the values stored in memory starting at address I
   I is set to I + X + 1 after operation */
void op_FX65(uint8_t vx) {
    printf("Not implemented.");
    return;
}