#include <stdio.h>

#include "esi_fmt.h"

void putchar_test(char c, void *arg);
int fctprintf(void (*out)(char character, void* arg), void* arg, const char* format, ...);

void putchar_test(char c, void *arg) {
    putchar(c);
}

int main(int argc, char *argv[]) {
    esi_fctprintf(putchar_test, NULL, "[INFO]: esi_fmt is functioning, 100 = %d, 15 = 0X%02X\n", 100, 15);
    esi_printf("[INFO]: 123 = %d, 15 = 0X%02X\n", 123, 15);
    return 0;
}