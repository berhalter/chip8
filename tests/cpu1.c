#include <criterion/criterion.h>
#include "../include/cpu.h"

/* if this test fails, you have serious problems. */
void test_init_cpu() {
    cpu *cpu;
    cpu = init_cpu();
    cr_assert_not_null(cpu, "CPU not initalized.");
    return;
}

void test_load_rom() {
    cr_assert_not_null(NULL, "Not implemented.");
    return;
}

Test(cpu, test1) { test_init_cpu(); }
Test(cpu, test2) { test_load_rom(); }