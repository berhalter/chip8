#include "../include/cpu.h"
#include "../include/op.h"

cpu *init_cpu() {
    /* TO-DO: specify when cpu should be freed by the program. */
    cpu *cpu;
    cpu = calloc(1, sizeof(*cpu));
    if (cpu == NULL) {
        perror("ERROR: Could not initialize CPU.\n");
        return NULL;
    }
    cpu->program_ct = START_ADDR;
    return cpu;
}

int load_rom(const char *filename, cpu *cpu) {
    FILE *rom = fopen(filename, "r");
    if (rom == NULL) {
        perror("ERROR: Could not open ROM file.\n");
        return 1;
    }
    if (fseek(rom, 0L, SEEK_END) != 0) {
        perror("ERROR: Could not obtain ROM file size.\n");
        return 2;
    }
    long size = ftell(rom);
    /* max_size is inaccurate due to the uppermost bytes being reserved on
       older 4K systems, but I'm unsure as to how much this actually matters.
       https://en.wikipedia.org/wiki/CHIP-8#Memory */
    long max_size = RAM_SIZE - START_ADDR;
    if (size == 0) {
        fprintf(stderr, "ERROR: ROM file is empty (0B).\n");
        return 3;
    } else if (size > max_size) {
        fprintf(stderr, "ERROR: ROM file is too large (>%ld).\n", max_size);
        return 4;
    }
    rewind(rom);
    memcpy((cpu->ram + START_ADDR), rom, size);
    if (fclose(rom) != 0) {
        perror("ERROR: Could not close ROM file.\n");
        return 5;
    }
    return 0;
}

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