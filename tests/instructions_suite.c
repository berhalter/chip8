#include <criterion/criterion.h>
#include "../include/instructions.h"

/* testing whether or not decode_instruction calls the correct instruction is
   difficult, but it may be possible to do implicitly by checking for effects
   of each instruction */

void fetch_is_big_endian() {
    return;
}

void decode_invalid_opcode() {
    return;
}


Test(fetch_decode, test0) { fetch_is_big_endian(); }
Test(fetch_decode, test1) { decode_invalid_opcode(); }

Test(op_0NNN, test0) { printf("No tests yet!\n"); }
Test(op_00E0, test0) { printf("No tests yet!\n"); }
Test(op_00EE, test0) { printf("No tests yet!\n"); }
Test(op_1NNN, test0) { printf("No tests yet!\n"); }
Test(op_2NNN, test0) { printf("No tests yet!\n"); }
Test(op_3XNN, test0) { printf("No tests yet!\n"); }
Test(op_4XNN, test0) { printf("No tests yet!\n"); }
Test(op_5XY0, test0) { printf("No tests yet!\n"); }
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