#include <criterion/criterion.h>
#include "../include/cpu.h"

/* if this test fails, you have serious problems. */
void cpu_not_null() {
    cpu_t *cpu;
    cpu = init_cpu();
    cr_assert_not_null(cpu, "cpu_not_null() failed. CPU not initalized.\n");
    return;
}

void cpu_null() {
    //Not sure if this is possible to test
    return;
}

void cpu_valid_pc() {
    cpu_t *cpu;
    cpu = init_cpu();
    uint16_t expected = START_ADDR;
    uint16_t actual = cpu->program_ct;
    cr_assert_eq(actual, expected, "cpu_valid_pc() failed.\nExpected: 0x%hx\nActual: 0x%hx\n", expected, actual);
    return;
}

void cpu_blank_display() {
    cpu_t *cpu;
    cpu = init_cpu();
    for (int y = 0; y < DISPLAY_H; ++y) {
        for (int x = 0; x < DISPLAY_W; ++x) {
            uint8_t expected = 0;
            uint8_t actual = cpu->display[y][x];
            cr_expect_eq(actual, expected, "cpu_blank_display() failed at (%dx, %dy).\nExpected: %hhd\nActual: %hhd\n", x, y, expected, actual);
        }
    }
}

void rom_opens() {
    cpu_t *cpu;
    cpu = init_cpu();
    int expected = 0;
    int actual = load_rom("./roms/IBMLogo.ch8", cpu);
    cr_assert_eq(actual, expected, "rom_opens() failed.\nExpected: %d\nActual: %d\n", expected, actual);
    return;
}

void rom_NULL_cpu() {
    cpu_t *cpu;
    cpu = NULL;
    int expected = 1;
    int actual = load_rom("./roms/IBMLogo.ch8", cpu);
    cr_assert_eq(actual, expected, "rom_NULL_cpu() failed.\nExpected: %d\nActual: %d\n", expected, actual);
    return;
}

void rom_invalid_filename() {
    cpu_t *cpu;
    cpu = init_cpu();
    int expected = 2;
    int actual = load_rom("Not a file", cpu);
    cr_assert_eq(actual, expected, "rom_invalid_filename() failed.\nExpected: %d\nActual: %d\n", expected, actual);
    return;
}

void rom_fseek_fail() {
    //Not sure if this is possible to test
    return;
}

void rom_empty() {
    cpu_t *cpu;
    cpu = init_cpu();
    int expected = 4;
    int actual = load_rom("./roms/unit_tests/empty.ch8", cpu);
    cr_assert_eq(actual, expected, "rom_empty() failed.\nExpected: %d\nActual: %d\n", expected, actual);
    return;
}

void rom_too_large_10000() {
    cpu_t *cpu;
    cpu = init_cpu();
    int expected = 5;
    int actual = load_rom("./roms/unit_tests/too_large_10000.ch8", cpu);
    cr_assert_eq(actual, expected, "rom_too_large_10000() failed.\nExpected: %d\nActual: %d\n", expected, actual);
    return;
}

void rom_max_size() {
    //the current max_size calculation is not correct, so this test will have to be added later.
    return;
}

void rom_max_size_plus1() {
    //the current max_size calculation is not correct, so this test will have to be added later.
    return;
}

void rom_fclose_fail() {
    //Not sure if this is possible to test
    return;
}


Test(init_cpu, test0) { cpu_not_null(); }
Test(init_cpu, test1) { cpu_null(); }
Test(init_cpu, test2) { cpu_valid_pc(); }
Test(init_cpu, test3) { cpu_blank_display(); }

Test(load_rom, test0) { rom_opens(); }
Test(load_rom, test1) { rom_NULL_cpu(); }
Test(load_rom, test2) { rom_invalid_filename(); }
Test(load_rom, test3) { rom_fseek_fail(); }
Test(load_rom, test4) { rom_empty(); }
Test(load_rom, test5) { rom_too_large_10000(); }
Test(load_rom, test6) { rom_max_size(); }
Test(load_rom, test7) { rom_max_size_plus1(); }
Test(load_rom, test8) { rom_fclose_fail(); }