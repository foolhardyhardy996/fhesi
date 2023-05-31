#include <stdio.h>

#include "esi_err_test.h"

int main(int argc, char *argv[]) {
    printf("[INFO]: check none message\n");
    printf("%s\n", esi_strerror(ESI_ERR(ESI_ERR_SRC_NONE, ESI_ERR_STATUS_NONE)));
    printf("[INFO]: check other message\n");
    printf("%s\n", esi_strerror(ESI_ERR(ESI_ERR_SRC_PART1, ESI_ERR_STATUS_BUSSY)));
    printf("%s\n", esi_strerror(ESI_ERR(ESI_ERR_SRC_PART2, ESI_ERR_STATUS_DEAD)));

    return 0;
}