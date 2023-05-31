#include <stdio.h>

#include "esi_str.h"

int main(int argc, char *argv[]) {
    const char *str1 = "abcd", *str2 = "abce";
    char buf[64];

    printf("[INFO]: test mempcy and strlen:\n");
    memcpy(buf, str1, strlen(str1));
    buf[strlen(str1)] = 0;
    printf("[INFO]: buf = %s, strlen(buf) = %d\n", buf, strlen(buf));

    return 0;
}