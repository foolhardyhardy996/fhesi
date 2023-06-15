#include <stdio.h>

#include "esi_arr.h"

ESI_ARR_TYPE_DECL(my_arr_t, int, 10);
ESI_ARR_TYPE_IMPL(my_arr_t, int, 10);

void print_elem(int index, int val);

void print_elem(int index, int val) {
    printf("arr[%d] = %d\n", index, val);
}

int main(int argc, char *argv[]) {
    //my_arr_t arr;
    ESI_ARR_DECL(my_arr_t, arr);
    ESI_ARR_ELEM_T(my_arr_t) val = 10;
    ESI_ARR_ELEM_PTR_T(my_arr_t) pval = &val;
    int i, ret;
    printf("[INFO]: start testing\n");
    printf("[INFO]: cap = %d, len = %d\n", ESI_ARR_CAP(my_arr_t, &arr), ESI_ARR_LEN(my_arr_t, &arr));
    for(i = 0; i < 15; i++) {
        printf("[INFO]: insert i = %d\n", i);
        ret = ESI_ARR_INSERT(my_arr_t, &arr, 0, i);
        if (ret != 0) {
            printf("[ERROR]: insert: %s\n", esi_arr_strerror(ret));
        }
        printf("[INFO]: cap = %d, len = %d\n", ESI_ARR_CAP(my_arr_t, &arr), ESI_ARR_LEN(my_arr_t, &arr));
    }
    for(i = 0; i < 5; i++) {
        printf("[INFO]: remove i = %d\n", i);
        ret = ESI_ARR_REMOVE(my_arr_t, &arr, 0);
        if (ret != 0) {
            printf("[ERROR]: remove: %s\n", esi_arr_strerror(ret));
        }
        printf("[INFO]: cap = %d, len = %d\n", ESI_ARR_CAP(my_arr_t, &arr), ESI_ARR_LEN(my_arr_t, &arr));
    }
    ESI_ARR_FOR_EACH_ELEM(my_arr_t, &arr, print_elem);
    printf("[INFO]: everything is fine.\n");

    return 0;
}