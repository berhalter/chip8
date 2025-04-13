#include "../include/global.h"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Missing arguments. Usage: chip8 file\n");
        exit(EXIT_FAILURE);
    }
    printf("ROM file: %s\n", argv[1]);
    return EXIT_SUCCESS;
}
