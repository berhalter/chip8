#include <criterion/criterion.h>
#include "../include/instructions.h"

cpu_t *cpu;

void setup() {
    cpu = init_cpu();
    cr_assert_not_null(cpu, "Test failed. CPU not initalized.\n");
}

void teardown() {
    free(cpu);
}

/* Notes: 
 * Testing whether or not decode_instruction calls the correct instruction is
   difficult, but it may be possible to do implicitly by checking for effects
   of each instruction
 * Should probably verify that values passed as registers do not exceed 0xF
*/

void fetch_is_big_endian() {
    return;
}

void decode_invalid_opcode1() {
    return;
}

void op_00E0_screen_is_cleared() {
    return;
}

void op_00EE_verify_program_ct() {
    return;
}

void op_00EE_verify_stack_ptr() {
    return;
}

void op_00EE_stack_ptr_is_zero() {
    return;
}

void op_3XNN_is_equal() {
    uint8_t vx = 0;
    uint8_t nnval = 123;
    cpu->registers[vx] = nnval;
    uint16_t pc = cpu->program_ct;
    op_3XNN(cpu, vx, nnval);
    uint16_t actual = cpu->program_ct;
    uint16_t expected = pc + 2;
    cr_assert_eq(actual, expected, "op_3XNN_is_equal() failed.\nExpected: 0x%hx\nActual: 0x%hx\n", expected, actual);
}

void op_3XNN_is_not_equal() {
    uint8_t vx = 0;
    uint8_t nnval = 123;
    cpu->registers[vx] = 1;
    uint16_t pc = cpu->program_ct;
    op_3XNN(cpu, vx, nnval);
    uint16_t actual = cpu->program_ct;
    uint16_t expected = pc;
    cr_assert_eq(actual, expected, "op_3XNN_is_not_equal() failed.\nExpected: 0x%hx\nActual: 0x%hx\n", expected, actual);
}

void op_4XNN_is_equal() {
    return;
}

void op_4XNN_is_not_equal() {
    return;
}

void op_5XY0_is_equal() {
    return;
}

void op_5XY0_is_not_equal() {
    return;
}

Test(fetch_decode, test0) { fetch_is_big_endian(); }
Test(fetch_decode, test1) { decode_invalid_opcode1(); }

Test(op_0NNN, test0) { printf("No tests yet!\n"); }

Test(op_00E0, test0) { op_00E0_screen_is_cleared(); }

Test(op_00EE, test0) { op_00EE_verify_program_ct(); }
Test(op_00EE, test1) { op_00EE_verify_stack_ptr(); }
Test(op_00EE, test2) { op_00EE_stack_ptr_is_zero(); }

Test(op_1NNN, test0) { printf("No tests yet!\n"); }

Test(op_2NNN, test0) { printf("No tests yet!\n"); }

Test(op_3XNN, test0, .init = setup, .fini = teardown) { op_3XNN_is_equal(); }
Test(op_3XNN, test1, .init = setup, .fini = teardown) { op_3XNN_is_not_equal(); }

Test(op_4XNN, test0) { op_4XNN_is_equal(); }
Test(op_4XNN, test1) { op_4XNN_is_not_equal(); }

Test(op_5XY0, test0) { op_5XY0_is_equal(); }
Test(op_5XY0, test1) { op_5XY0_is_not_equal(); }

Test(op_6XNN, test0) { printf("No tests yet!\n"); }

Test(op_7XNN, test0) { printf("No tests yet!\n"); }

Test(op_8XY0, test0) { printf("No tests yet!\n"); }

Test(op_8XY1, test0) { printf("No tests yet!\n"); }

Test(op_8XY2, test0) { printf("No tests yet!\n"); }

Test(op_8XY3, test0) { printf("No tests yet!\n"); }

Test(op_8XY4, test0) { printf("No tests yet!\n"); }

Test(op_8XY5, test0) { printf("No tests yet!\n"); }

Test(op_8XY6, test0) { printf("No tests yet!\n"); }

Test(op_8XY7, test0) { printf("No tests yet!\n"); }

Test(op_8XYE, test0) { printf("No tests yet!\n"); }

Test(op_9XY0, test0) { printf("No tests yet!\n"); }

Test(op_ANNN, test0) { printf("No tests yet!\n"); }

Test(op_BNNN, test0) { printf("No tests yet!\n"); }

Test(op_CXNN, test0) { printf("No tests yet!\n"); }

Test(op_DXYN, test0) { printf("No tests yet!\n"); }

Test(op_EX9E, test0) { printf("No tests yet!\n"); }

Test(op_EXA1, test0) { printf("No tests yet!\n"); }

Test(op_FX07, test0) { printf("No tests yet!\n"); }

Test(op_FX0A, test0) { printf("No tests yet!\n"); }

Test(op_FX15, test0) { printf("No tests yet!\n"); }

Test(op_FX18, test0) { printf("No tests yet!\n"); }

Test(op_FX1E, test0) { printf("No tests yet!\n"); }

Test(op_FX29, test0) { printf("No tests yet!\n"); }

Test(op_FX33, test0) { printf("No tests yet!\n"); }

Test(op_FX55, test0) { printf("No tests yet!\n"); }

Test(op_FX65, test0) { printf("No tests yet!\n"); }