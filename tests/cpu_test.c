#include <criterion/criterion.h>
#include "../include/cpu.h"

/* if this test fails, you have serious problems. */
void test_init() {
    cpu *cpu;
    cpu = init_cpu();
    cr_assert_not_null(cpu, "CPU not initalized.");
    return;
}

void test_load() {
    cr_assert_not_null(NULL, "Not implemented.");
    return;
}

void test_fetch() {
    cr_assert_not_null(NULL, "Not implemented.");
    return;
}

void test_decode() {
    cr_assert_not_null(NULL, "Not implemented.");
    return;
}

Test(cpu, test1) { test_init(); }
Test(cpu, test2) { test_load(); }
Test(cpu, test3) { test_fetch(); }
Test(cpu, test4) { test_decode(); }