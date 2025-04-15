#include "../include/instructions.h"


uint16_t fetch_instruction(cpu_t *cpu) {
    /* All opcodes occupy 2 bytes of memory. Note that CHIP-8 is big-endian,
       but x86 is not, so type-casting the array as a pointer won't work here */
    uint8_t msb = cpu->ram[cpu->program_ct];
    uint8_t lsb = cpu->ram[cpu->program_ct + 1];
    uint16_t opcode = (msb << 8) + lsb;
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
            op_00EE(cpu);
            break;
        default:
            /* It should be safe to assume that the last 3 digits are an address in this case.
               However, this instruction doesn't need to be implemented because the interpreter
               itself can't execute machine language code. */
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
        op_2NNN(cpu, address);
        break;
    case 0x3000:
        vx = (opcode >> 8) & 0x0F;
        nnval = opcode & 0x00FF;
        op_3XNN(cpu, vx, nnval);
        break;
    case 0x4000:
        vx = (opcode >> 8) & 0x0F;
        nnval = opcode & 0x00FF;
        op_4XNN(cpu, vx, nnval);
        break;
    case 0x5000:
        switch (opcode & 0x000F) {
        case 0x0000:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_5XY0(cpu, vx, vy);
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
            op_8XY0(cpu, vx, vy);
            break;
        case 0x0001:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY1(cpu, vx, vy);
            break;
        case 0x0002:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY2(cpu, vx, vy);
            break;
        case 0x0003:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY3(cpu, vx, vy);
            break;
        case 0x0004:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY4(cpu, vx, vy);
            break;
        case 0x0005:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY5(cpu, vx, vy);
            break;
        case 0x0006:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY6(cpu, vx, vy);
            break;
        case 0x0007:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XY7(cpu, vx, vy);
            break;
        case 0x000E:
            vx = (opcode >> 8) & 0x0F;
            vy = (opcode >> 4) & 0x0F;
            op_8XYE(cpu, vx, vy);
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
            op_9XY0(cpu, vx, vy);
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
        op_BNNN(cpu, address);
        break;
    case 0xC000:
        vx = (opcode >> 8) & 0x0F;
        nnval = opcode & 0x00FF;
        op_CXNN(cpu, vx, nnval);
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
            op_EX9E(cpu, vx);
            break;
        case 0x00A1:
            vx = (opcode >> 8) & 0x0F;
            op_EXA1(cpu, vx);
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
            op_FX07(cpu, vx);
            break;
        case 0x000A:
            vx = (opcode >> 8) & 0x0F;
            op_FX0A(cpu, vx);
            break;
        case 0x0015:
            vx = (opcode >> 8) & 0x0F;
            op_FX15(cpu, vx);
            break;
        case 0x0018:
            vx = (opcode >> 8) & 0x0F;
            op_FX18(cpu, vx);
            break;
        case 0x001E:
            vx = (opcode >> 8) & 0x0F;
            op_FX1E(cpu, vx);
            break;
        case 0x0029:
            vx = (opcode >> 8) & 0x0F;
            op_FX29(cpu, vx);
            break;
        case 0x0033:
            vx = (opcode >> 8) & 0x0F;
            op_FX33(cpu, vx);
            break;
        case 0x0055:
            vx = (opcode >> 8) & 0x0F;
            op_FX55(cpu, vx);
            break;
        case 0x0065:
            vx = (opcode >> 8) & 0x0F;
            op_FX65(cpu, vx);
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
void op_00EE(cpu_t *cpu) {
    cpu->program_ct = cpu->stack[cpu->stack_ptr];
    (cpu->stack_ptr)--;
    return;
}

/* Jump to address NNN */
void op_1NNN(cpu_t *cpu, uint16_t address) {
    cpu->program_ct = address;
    return;
}

/* Execute subroutine starting at address NNN */
void op_2NNN(cpu_t *cpu, uint16_t address) {
    (cpu->stack_ptr)++;
    cpu->stack[cpu->stack_ptr] = cpu->program_ct;
    cpu->program_ct = address;
    return;
}

/* Skip the following instruction if the value of register VX equals NN  */
void op_3XNN(cpu_t *cpu, uint8_t vx, uint8_t nnval) {
    if (cpu->registers[vx] == nnval) {
        cpu->program_ct += 2;
    }
    return;
}

/* Skip the following instruction if the value of register VX is not equal to NN */
void op_4XNN(cpu_t *cpu, uint8_t vx, uint8_t nnval) {
    if (cpu->registers[vx] != nnval) {
        cpu->program_ct += 2;
    }
    return;
}

/* Skip the following instruction if the value of register VX is equal to the value of register VY */
void op_5XY0(cpu_t *cpu, uint8_t vx, uint8_t vy) {
    if (cpu->registers[vx] == cpu->registers[vy]) {
        cpu->program_ct += 2;
    }
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
void op_8XY0(cpu_t *cpu, uint8_t vx, uint8_t vy) {
    cpu->registers[vx] = cpu->registers[vy];
    return;
}

/* Set VX to VX OR VY */
void op_8XY1(cpu_t *cpu, uint8_t vx, uint8_t vy) {
    cpu->registers[vx] |= cpu->registers[vy];
    return;
}

/* Set VX to VX AND VY */
void op_8XY2(cpu_t *cpu, uint8_t vx, uint8_t vy) {
    cpu->registers[vx] &= cpu->registers[vy];
    return;
}

/* Set VX to VX XOR VY */
void op_8XY3(cpu_t *cpu, uint8_t vx, uint8_t vy) {
    cpu->registers[vx] ^= cpu->registers[vy];
    return;
}

/* Add the value of register VY to register VX
   Set VF to 01 if a carry occurs
   Set VF to 00 if a carry does not occur */
void op_8XY4(cpu_t *cpu, uint8_t vx, uint8_t vy) {
    uint8_t no_carry_max = UINT8_MAX - cpu->registers[vx];
    uint8_t vf = 0x0F;
    if (cpu->registers[vy] > no_carry_max) {
        cpu->registers[vf] = 1;
    } else {
        cpu->registers[vf] = 0;
    }
    cpu->registers[vx] += cpu->registers[vy];
    return;
}

/* Subtract the value of register VY from register VX
   Set VF to 00 if a borrow occurs
   Set VF to 01 if a borrow does not occur */
void op_8XY5(cpu_t *cpu, uint8_t vx, uint8_t vy) {
    uint8_t vf = 0x0F;
    if (cpu->registers[vy] > cpu->registers[vx]) {
        cpu->registers[vf] = 0;
    } else {
        cpu->registers[vf] = 1;
    }
    cpu->registers[vx] -= cpu->registers[vy];
    return;
}

/* Store the value of register VY shifted right one bit in register VX
   Set register VF to the least significant bit prior to the shift
   VY is unchanged */
void op_8XY6(cpu_t *cpu, uint8_t vx, uint8_t vy) {
    uint8_t vf = 0x0F;
    cpu->registers[vf] = cpu->registers[vy] & 0x01;
    cpu->registers[vx] = cpu->registers[vy] >> 1;
    return;
}

/* Set register VX to the value of VY minus VX
   Set VF to 00 if a borrow occurs
   Set VF to 01 if a borrow does not occur*/
void op_8XY7(cpu_t *cpu, uint8_t vx, uint8_t vy) {
    uint8_t vf = 0x0F;
    if (cpu->registers[vx] > cpu->registers[vy]) {
        cpu->registers[vf] = 0;
    } else {
        cpu->registers[vf] = 1;
    }
    cpu->registers[vx] = cpu->registers[vy] - cpu->registers[vx];
    return;
}

/* Store the value of register VY shifted left one bit in register VX
   Set register VF to the most significant bit prior to the shift
   VY is unchanged*/
void op_8XYE(cpu_t *cpu, uint8_t vx, uint8_t vy) {
    uint8_t vf = 0x0F;
    cpu->registers[vf] = cpu->registers[vy] & 0x80;
    cpu->registers[vx] = cpu->registers[vy] << 1;
    return;
}

/* Skip the following instruction if the value of register VX is not equal to the value of register VY */
void op_9XY0(cpu_t *cpu, uint8_t vx, uint8_t vy) {
    if (cpu->registers[vx] != cpu->registers[vy]) {
        cpu->program_ct += 2;
    }
    return;
}

/* Store memory address NNN in register I */
void op_ANNN(cpu_t *cpu, uint16_t address) {
    cpu->index = address;
    return;
}

/* Jump to address NNN + V0 */
void op_BNNN(cpu_t *cpu, uint16_t address) {
    uint8_t v0 = 0x00;
    cpu->program_ct = address + cpu->registers[v0];
    return;
}

/* Set VX to a random number with a mask of NN */
void op_CXNN(cpu_t *cpu, uint8_t vx, uint8_t nnval) {
    cpu->registers[vx] = rand() & nnval;
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
void op_EX9E(cpu_t *cpu, uint8_t vx) {
    (void) vx;
    cpu->sound_timer++;
    printf("op_EX9E not implemented.\n");
    return;
}

/* Skip the following instruction if the key corresponding to the hex value currently stored in register VX is not pressed */
void op_EXA1(cpu_t *cpu, uint8_t vx) {
    (void) vx;
    cpu->sound_timer++;
    printf("op_EXA1 not implemented.\n");
    return;
}

/* Store the current value of the delay timer in register VX */
void op_FX07(cpu_t *cpu, uint8_t vx) {
    cpu->registers[vx] = cpu->delay_timer;
    return;
}

/* Wait for a keypress and store the result in register VX */
void op_FX0A(cpu_t *cpu, uint8_t vx) {
    (void) vx;
    cpu->sound_timer++;
    printf("op_FX0A not implemented.\n");
    return;
}

/* Set the delay timer to the value of register VX */
void op_FX15(cpu_t *cpu, uint8_t vx) {
    cpu->delay_timer = cpu->registers[vx];
    return;
}

/* Set the sound timer to the value of register VX */
void op_FX18(cpu_t *cpu, uint8_t vx) {
    cpu->sound_timer = cpu->registers[vx];
    return;
}

/* Add the value stored in register VX to register I 
  src: https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#fx1e-add-to-index
  "Unlike other arithmetic instructions, this did not affect VF on overflow on
  the original COSMAC VIP. However, it seems that some interpreters set VF to 1
  if I “overflows” from 0FFF to above 1000 (outside the normal addressing
  range). This wasn’t the case on the original COSMAC VIP, at least, but
  apparently the CHIP-8 interpreter for Amiga behaved this way. At least one
  known game, Spacefight 2091!, relies on this behavior. I don’t know of any
  games that rely on this *not* happening, so perhaps it’s safe to do it like
  the Amiga interpreter did."*/
void op_FX1E(cpu_t *cpu, uint8_t vx) {
    /* It would probably be fine to just check if vx > 0x0FFF, but this should
       also work in the case that index actually overflows a uint16_t */
    uint16_t index_max = 0x0FFF;
    uint16_t no_carry_max = index_max - cpu->index;
    uint8_t vf = 0x0F;
    if (cpu->registers[vx] > no_carry_max) {
        cpu->registers[vf] = 1;
    }
    cpu->index += cpu->registers[vx];
    return;
}

/* Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX */
void op_FX29(cpu_t *cpu, uint8_t vx) {
    (void) vx;
    cpu->sound_timer++;
    printf("op_FX29 not implemented.\n");
    return;
}

/* Store the binary-coded decimal equivalent of the value stored in register VX at addresses I, I + 1, and I + 2 */
void op_FX33(cpu_t *cpu, uint8_t vx) {
    (void) vx;
    cpu->sound_timer++;
    printf("op_FX33 not implemented.\n");
    return;
}

/* Store the values of registers V0 to VX inclusive in memory starting at address I
   I is set to I + X + 1 after operation */
void op_FX55(cpu_t *cpu, uint8_t vx) {
    (void) vx;
    cpu->sound_timer++;
    printf("op_FX55 not implemented.\n");
    return;
}

/* Fill registers V0 to VX inclusive with the values stored in memory starting at address I
   I is set to I + X + 1 after operation */
void op_FX65(cpu_t *cpu, uint8_t vx) {
    (void) vx;
    cpu->sound_timer++;
    printf("op_FX65 not implemented.\n");
    return;
}