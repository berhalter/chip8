#include "../include/instructions.h"


uint16_t fetch_instruction(cpu *cpu) {
    /* All opcodes occupy 2 bytes of memory. Note that CHIP-8 is big-endian,
       but x86 is not, so type-casting the array as a pointer won't work here */
    uint8_t msb = cpu->ram[cpu->program_ct];
    uint8_t lsb = cpu->ram[cpu->program_ct + 1];
    uint16_t opcode = (msb << 8) + lsb;
    cpu->program_ct += 2;
    return opcode;
}

int decode_instruction(uint16_t opcode) {
    uint16_t address;
    uint8_t vx, vy, nnval, nval;
    int retval = 0;
    switch (opcode & 0xF000) {
    case 0x0000:
        switch (opcode) {
        case 0x00E0:
            op_00E0();
            break;
        case 0x00EE:
            op_00EE();
            break;
        default:
            /* It should be safe to assume that the last 3 digits are an address in this case.
               The instruction needs to assert that the address is valid, however. */
            address = opcode & 0x0FFF;
            op_0NNN(address);
            break;
        }
        break;
    case 0x1000:
        address = opcode & 0x0FFF;
        op_1NNN(address);
        break;
    case 0x2000:
        address = opcode & 0x0FFF;
        op_2NNN(address);
        break;
    case 0x3000:
        vx = (opcode >> 8) & 0x0F;
        nnval = opcode & 0x00FF;
        op_3XNN(vx, nnval);
        break;
    case 0x4000:
        vx = (opcode >> 8) & 0x0F;
        nnval = opcode & 0x00FF;
        op_4XNN(vx, nnval);
        break;
    case 0x5000:
        switch (opcode & 0x000F) {
        case 0x0000:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_5XY0(vx, vy);
            break;
        default:
            fprintf(stderr, "ERROR: Invalid opcode (0x%x)\n", opcode);
            retval = 1;
            break;
        }
        break;
    case 0x6000:
        vx = (opcode >> 8) & 0x0F;
        nnval = opcode & 0x00FF;
        op_6XNN(vx, nnval);
        break;
    case 0x7000:
        vx = (opcode >> 8) & 0x0F;
        nnval = opcode & 0x00FF;
        op_7XNN(vx, nnval);
        break;
    case 0x8000:
        switch (opcode & 0x000F) {
        case 0x0000:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY0(vx, vy);
            break;
        case 0x0001:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY1(vx, vy);
            break;
        case 0x0002:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY2(vx, vy);
            break;
        case 0x0003:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY3(vx, vy);
            break;
        case 0x0004:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY4(vx, vy);
            break;
        case 0x0005:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY5(vx, vy);
            break;
        case 0x0006:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY6(vx, vy);
            break;
        case 0x0007:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY7(vx, vy);
            break;
        case 0x000E:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XYE(vx, vy);
            break;
        default:
            fprintf(stderr, "ERROR: Invalid opcode (0x%x)\n", opcode);
            retval = 2;
            break;
        }
        break;
    case 0x9000:
        switch (opcode & 0x000F) {
        case 0x0000:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_9XY0(vx, vy);
            break;
        default:
            fprintf(stderr, "ERROR: Invalid opcode (0x%x)\n", opcode);
            retval = 3;
            break;
        }
        break;
    case 0xA000:
        address = opcode & 0x0FFF;
        op_ANNN(address);
        break;
    case 0xB000:
        address = opcode & 0x0FFF;
        op_BNNN(address);
        break;
    case 0xC000:
        vx = (opcode >> 8) & 0x0F;
        nnval = opcode & 0x00FF;
        op_CXNN(vx, nnval);
        break;
    case 0xD000:
        vx = (opcode >> 8) & 0x0F;
        vy = (opcode >> 4) & 0x0F;
        nval = opcode & 0xF;
        op_DXYN(vx, vy, nval);
        break;
    case 0xE000:
        switch (opcode & 0x00FF) {
        case 0x009E:
            vx = (opcode >> 8) & 0x0F;
            op_EX9E(vx);
            break;
        case 0x00A1:
            vx = (opcode >> 8) & 0x0F;
            op_EXA1(vx);
            break;
        default:
            fprintf(stderr, "ERROR: Invalid opcode (0x%x)\n", opcode);
            retval = 4;
            break;
        }
        break;
    case 0xF000:
        switch (opcode & 0x00FF) {
        case 0x0007:
            vx = (opcode >> 8) & 0x0F;
            op_FX07(vx);
            break;
        case 0x000A:
            vx = (opcode >> 8) & 0x0F;
            op_FX0A(vx);
            break;
        case 0x0015:
            vx = (opcode >> 8) & 0x0F;
            op_FX15(vx);
            break;
        case 0x0018:
            vx = (opcode >> 8) & 0x0F;
            op_FX18(vx);
            break;
        case 0x001E:
            vx = (opcode >> 8) & 0x0F;
            op_FX1E(vx);
            break;
        case 0x0029:
            vx = (opcode >> 8) & 0x0F;
            op_FX29(vx);
            break;
        case 0x0033:
            vx = (opcode >> 8) & 0x0F;
            op_FX33(vx);
            break;
        case 0x0055:
            vx = (opcode >> 8) & 0x0F;
            op_FX55(vx);
            break;
        case 0x0065:
            vx = (opcode >> 8) & 0x0F;
            op_FX65(vx);
            break;
        default:
            fprintf(stderr, "ERROR: Invalid opcode (0x%x)\n", opcode);
            retval = 5;
            break;
        }
        break;
    default:
        fprintf(stderr, "ERROR: Invalid opcode (0x%x)\n", opcode);
        retval = 6;
        break;
    }
    return retval;
}


/* OPCODES */

/* Execute machine language subroutine at address NNN */
void op_0NNN(uint16_t address) {
    (void) address;
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
    (void) address;
    printf("Not implemented.");
    return;
}

/* Execute subroutine starting at address NNN */
void op_2NNN(uint16_t address) {
    (void) address;
    printf("Not implemented.");
    return;
}

/* Skip the following instruction if the value of register VX equals NN  */
void op_3XNN(uint8_t vx, uint8_t nnval) {
    (void) vx;
    (void) nnval;
    printf("Not implemented.");
    return;
}

/* Skip the following instruction if the value of register VX is not equal to NN */
void op_4XNN(uint8_t vx, uint8_t nnval) {
    (void) vx;
    (void) nnval;
    printf("Not implemented.");
    return;
}

/* Skip the following instruction if the value of register VX is equal to the value of register VY */
void op_5XY0(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("Not implemented.");
    return;
}

/* Store number NN in register VX */
void op_6XNN(uint8_t vx, uint8_t nnval) {
    (void) vx;
    (void) nnval;
    printf("Not implemented.");
    return;
}

/* Add the value NN to register VX */
void op_7XNN(uint8_t vx, uint8_t nnval) {
    (void) vx;
    (void) nnval;
    printf("Not implemented.");
    return;
}

/* Store the value of register VY in register VX */
void op_8XY0(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("Not implemented.");
    return;
}

/* Set VX to VX OR VY */
void op_8XY1(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("Not implemented.");
    return;
}

/* Set VX to VX AND VY */
void op_8XY2(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("Not implemented.");
    return;
}

/* Set VX to VX XOR VY */
void op_8XY3(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("Not implemented.");
    return;
}

/* Add the value of register VY to register VX
   Set VF to 01 if a carry occurs
   Set VF to 00 if a carry does not occur */
void op_8XY4(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("Not implemented.");
    return;
}

/* Subtract the value of register VY from register VX
   Set VF to 00 if a borrow occurs
   Set VF to 01 if a borrow does not occur */
void op_8XY5(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("Not implemented.");
    return;
}

/* Store the value of register VY shifted right one bit in register VX
   Set register VF to the least significant bit prior to the shift
   VY is unchanged */
void op_8XY6(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("Not implemented.");
    return;
}

/* Set register VX to the value of VY minus VX
   Set VF to 00 if a borrow occurs
   Set VF to 01 if a borrow does not occur*/
void op_8XY7(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("Not implemented.");
    return;
}

/* Store the value of register VY shifted left one bit in register VX
   Set register VF to the most significant bit prior to the shift
   VY is unchanged*/
void op_8XYE(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("Not implemented.");
    return;
}

/* Skip the following instruction if the value of register VX is not equal to the value of register VY */
void op_9XY0(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("Not implemented.");
    return;
}

/* Store memory address NNN in register I */
void op_ANNN(uint16_t address) {
    (void) address;
    printf("Not implemented.");
    return;
}

/* Jump to address NNN + V0 */
void op_BNNN(uint16_t address) {
    (void) address;
    printf("Not implemented.");
    return;
}

/* Set VX to a random number with a mask of NN */
void op_CXNN(uint8_t vx, uint8_t nnval) {
    (void) vx;
    (void) nnval;
    printf("Not implemented.");
    return;
}

/* Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
   Set VF to 01 if any set pixels are changed to unset, and 00 otherwise */
void op_DXYN(uint8_t vx, uint8_t vy, uint8_t nval) {
    (void) vx;
    (void) vy;
    (void) nval;
    printf("Not implemented.");
    return;
}

/* Skip the following instruction if the key corresponding to the hex value currently stored in register VX is pressed */
void op_EX9E(uint8_t vx) {
    (void) vx;
    printf("Not implemented.");
    return;
}

/* Skip the following instruction if the key corresponding to the hex value currently stored in register VX is not pressed */
void op_EXA1(uint8_t vx) {
    (void) vx;
    printf("Not implemented.");
    return;
}

/* Store the current value of the delay timer in register VX */
void op_FX07(uint8_t vx) {
    (void) vx;
    printf("Not implemented.");
    return;
}

/* Wait for a keypress and store the result in register VX */
void op_FX0A(uint8_t vx) {
    (void) vx;
    printf("Not implemented.");
    return;
}

/* Set the delay timer to the value of register VX */
void op_FX15(uint8_t vx) {
    (void) vx;
    printf("Not implemented.");
    return;
}

/* Set the sound timer to the value of register VX */
void op_FX18(uint8_t vx) {
    (void) vx;
    printf("Not implemented.");
    return;
}

/* Add the value stored in register VX to register I */
void op_FX1E(uint8_t vx) {
    (void) vx;
    printf("Not implemented.");
    return;
}

/* Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX */
void op_FX29(uint8_t vx) {
    (void) vx;
    printf("Not implemented.");
    return;
}

/* Store the binary-coded decimal equivalent of the value stored in register VX at addresses I, I + 1, and I + 2 */
void op_FX33(uint8_t vx) {
    (void) vx;
    printf("Not implemented.");
    return;
}

/* Store the values of registers V0 to VX inclusive in memory starting at address I
   I is set to I + X + 1 after operation */
void op_FX55(uint8_t vx) {
    (void) vx;
    printf("Not implemented.");
    return;
}

/* Fill registers V0 to VX inclusive with the values stored in memory starting at address I
   I is set to I + X + 1 after operation */
void op_FX65(uint8_t vx) {
    (void) vx;
    printf("Not implemented.");
    return;
}