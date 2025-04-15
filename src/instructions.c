#include "../include/instructions.h"


uint16_t fetch_instruction(cpu_t *cpu) {
    /* All opcodes occupy 2 bytes of memory. Note that CHIP-8 is big-endian,
       but x86 is not, so type-casting the array as a pointer won't work here */
    uint8_t msb = cpu->ram[cpu->program_ct];
    uint8_t lsb = cpu->ram[cpu->program_ct + 1];
    uint16_t opcode = (msb << 8) + lsb;
    //printf("msb:%.2hhx, lsb:%.2hhx, opcode: %.4hx, pc:%.4hx\n", msb, lsb, opcode, cpu->program_ct);
    cpu->program_ct += 2;
    return opcode;
}

int decode_instruction(cpu_t *cpu, uint16_t opcode) {
    uint16_t address;
    uint8_t vx, vy, nnval, nval;
    int retval = 0;
    switch (opcode & 0xF000) {
    case 0x0000:
        switch (opcode) {
        case 0x00E0:
            op_00E0(cpu);
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
        op_1NNN(cpu, address);
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
        op_6XNN(cpu, vx, nnval);
        break;
    case 0x7000:
        vx = (opcode >> 8) & 0x0F;
        nnval = opcode & 0x00FF;
        op_7XNN(cpu, vx, nnval);
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
        op_ANNN(cpu, address);
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
        op_DXYN(cpu, vx, vy, nval);
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
    printf("op_0NNN not implemented.\n");
    return;
}

/* Clear the screen */
void op_00E0(cpu_t *cpu) {
    for (int y = 0; y < DISPLAY_H; ++y) {
        for (int x = 0; x < DISPLAY_W; ++x) {
            cpu->display[y][x] = 0;
        }
    }
    return;
}

/* Return from a subroutine */
void op_00EE() {
    printf("op_00EE not implemented.\n");
    return;
}

/* Jump to address NNN */
void op_1NNN(cpu_t *cpu, uint16_t address) {
    cpu->program_ct = address;
    return;
}

/* Execute subroutine starting at address NNN */
void op_2NNN(uint16_t address) {
    (void) address;
    printf("op_2NNN not implemented.\n");
    return;
}

/* Skip the following instruction if the value of register VX equals NN  */
void op_3XNN(uint8_t vx, uint8_t nnval) {
    (void) vx;
    (void) nnval;
    printf("op_3XNN not implemented.\n");
    return;
}

/* Skip the following instruction if the value of register VX is not equal to NN */
void op_4XNN(uint8_t vx, uint8_t nnval) {
    (void) vx;
    (void) nnval;
    printf("op_4XNN not implemented.\n");
    return;
}

/* Skip the following instruction if the value of register VX is equal to the value of register VY */
void op_5XY0(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("op_5XY0 not implemented.\n");
    return;
}

/* Store number NN in register VX */
void op_6XNN(cpu_t *cpu, uint8_t vx, uint8_t nnval) {
    cpu->registers[vx] = nnval;
    return;
}

/* Add the value NN to register VX */
void op_7XNN(cpu_t *cpu, uint8_t vx, uint8_t nnval) {
    cpu->registers[vx] += nnval;
    return;
}

/* Store the value of register VY in register VX */
void op_8XY0(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("op_8XY0 not implemented.\n");
    return;
}

/* Set VX to VX OR VY */
void op_8XY1(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("op_8XY1 not implemented.\n");
    return;
}

/* Set VX to VX AND VY */
void op_8XY2(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("op_8XY2 not implemented.\n");
    return;
}

/* Set VX to VX XOR VY */
void op_8XY3(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("op_8XY3 not implemented.\n");
    return;
}

/* Add the value of register VY to register VX
   Set VF to 01 if a carry occurs
   Set VF to 00 if a carry does not occur */
void op_8XY4(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("op_8XY4 not implemented.\n");
    return;
}

/* Subtract the value of register VY from register VX
   Set VF to 00 if a borrow occurs
   Set VF to 01 if a borrow does not occur */
void op_8XY5(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("op_8XY5 not implemented.\n");
    return;
}

/* Store the value of register VY shifted right one bit in register VX
   Set register VF to the least significant bit prior to the shift
   VY is unchanged */
void op_8XY6(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("op_8XY6 not implemented.\n");
    return;
}

/* Set register VX to the value of VY minus VX
   Set VF to 00 if a borrow occurs
   Set VF to 01 if a borrow does not occur*/
void op_8XY7(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("op_8XY7 not implemented.\n");
    return;
}

/* Store the value of register VY shifted left one bit in register VX
   Set register VF to the most significant bit prior to the shift
   VY is unchanged*/
void op_8XYE(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("op_8XYE not implemented.\n");
    return;
}

/* Skip the following instruction if the value of register VX is not equal to the value of register VY */
void op_9XY0(uint8_t vx, uint8_t vy) {
    (void) vx;
    (void) vy;
    printf("op_9XY0 not implemented.\n");
    return;
}

/* Store memory address NNN in register I */
void op_ANNN(cpu_t *cpu, uint16_t address) {
    cpu->index = address;
    return;
}

/* Jump to address NNN + V0 */
void op_BNNN(uint16_t address) {
    (void) address;
    printf("op_BNNN not implemented.\n");
    return;
}

/* Set VX to a random number with a mask of NN */
void op_CXNN(uint8_t vx, uint8_t nnval) {
    (void) vx;
    (void) nnval;
    printf("op_CXNN not implemented.\n");
    return;
}

/* Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
   Set VF to 01 if any set pixels are changed to unset, and 00 otherwise */
void op_DXYN(cpu_t *cpu, uint8_t vx, uint8_t vy, uint8_t nval) {
    /* The starting position should wrap around to the opposite side of the
       screen if the position coordinate is greater than the dimensions of
       the screen. NOTE: this does NOT apply once the sprite is being drawn;
       any sprite data that spills over the screen edge will not be drawn. */
    int start_x = cpu->registers[vx] % DISPLAY_W;
    int start_y = cpu->registers[vy] % DISPLAY_H;
    uint8_t vf = 0xF;
    cpu->registers[vf] = 0;
    for (uint8_t row = 0; row < nval; ++row) {
        int draw_y = start_y + row;
        if (draw_y >= DISPLAY_H - 1) {
            break;
        } else {
            uint16_t sprite_address = cpu->index + row;
            uint8_t sprite_data = cpu->ram[sprite_address];
            int sprite_len = 8;
            for (int column = 0; column < sprite_len; ++column) {
                int draw_x = start_x + column;
                if (draw_x >= DISPLAY_W - 1) {
                    break;
                } else {
                    int shift_amt = sprite_len - column - 1;
                    uint8_t sprite_px = (sprite_data >> shift_amt) & 0x0001; /* Technically the mask is unnecessary for the first iteration, but is needed afterwards to zero-out higher order bits. */
                    cpu->display[draw_y][draw_x] = cpu->display[draw_y][draw_x] ^ sprite_px;
                    if ((sprite_px == 1) && (cpu->display[draw_y][draw_x])) {
                        cpu->registers[vf] = 1;
                    }
                    
                }
            }
        }
    }
    return;
}

/* Skip the following instruction if the key corresponding to the hex value currently stored in register VX is pressed */
void op_EX9E(uint8_t vx) {
    (void) vx;
    printf("op_EX9E not implemented.\n");
    return;
}

/* Skip the following instruction if the key corresponding to the hex value currently stored in register VX is not pressed */
void op_EXA1(uint8_t vx) {
    (void) vx;
    printf("op_EXA1 not implemented.\n");
    return;
}

/* Store the current value of the delay timer in register VX */
void op_FX07(uint8_t vx) {
    (void) vx;
    printf("op_FX07 not implemented.\n");
    return;
}

/* Wait for a keypress and store the result in register VX */
void op_FX0A(uint8_t vx) {
    (void) vx;
    printf("op_FX0A not implemented.\n");
    return;
}

/* Set the delay timer to the value of register VX */
void op_FX15(uint8_t vx) {
    (void) vx;
    printf("op_FX15 not implemented.\n");
    return;
}

/* Set the sound timer to the value of register VX */
void op_FX18(uint8_t vx) {
    (void) vx;
    printf("op_FX18 not implemented.\n");
    return;
}

/* Add the value stored in register VX to register I */
void op_FX1E(uint8_t vx) {
    (void) vx;
    printf("op_FX1E not implemented.\n");
    return;
}

/* Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX */
void op_FX29(uint8_t vx) {
    (void) vx;
    printf("op_FX29 not implemented.\n");
    return;
}

/* Store the binary-coded decimal equivalent of the value stored in register VX at addresses I, I + 1, and I + 2 */
void op_FX33(uint8_t vx) {
    (void) vx;
    printf("op_FX33 not implemented.\n");
    return;
}

/* Store the values of registers V0 to VX inclusive in memory starting at address I
   I is set to I + X + 1 after operation */
void op_FX55(uint8_t vx) {
    (void) vx;
    printf("op_FX55 not implemented.\n");
    return;
}

/* Fill registers V0 to VX inclusive with the values stored in memory starting at address I
   I is set to I + X + 1 after operation */
void op_FX65(uint8_t vx) {
    (void) vx;
    printf("op_FX65 not implemented.\n");
    return;
}