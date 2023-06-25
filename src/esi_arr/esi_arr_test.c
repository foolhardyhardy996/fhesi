#include <stdio.h>

#include "esi_arr.h"

ESI_ARR_TYPE_DECL(my_arr_t, int, 10);
ESI_ARR_TYPE_IMPL(my_arr_t, int, 10);

void print_elem(int index, int *val);

void print_elem(int index, int *val) {
    printf("arr[%d] = %d\n", index, *val);
}

int predicate_gt15(int *val);
int predicate_gt15(int *val) {
    return *val > 15;
}

int predicate_lt0(int *val);
int predicate_lt0(int *val) {
    return *val < 0;
}

int predicate_eq20(int *val);
int predicate_eq20(int *val) {
    return *val == 20;
}

int predicate_eq17(int *val);
int predicate_eq17(int *val) {
    return *val == 17;
}

int main(int argc, char *argv[]) {
    //my_arr_t arr;
    ESI_ARR_DECL(my_arr_t, arr);
    ESI_ARR_ELEM_T(my_arr_t) val = 10;
    ESI_ARR_ELEM_PTR_T(my_arr_t) pval = &val;
    int i, ret;
    int onehundred = 100;
    int three = 3;
    printf("[INFO]: start testing\n");
    printf("[INFO]: cap = %d, len = %d\n", ESI_ARR_CAP(my_arr_t, &arr), ESI_ARR_LEN(my_arr_t, &arr));
    for(i = 0; i < 15; i++) {
        printf("[INFO]: insert i = %d\n", i);
        ret = ESI_ARR_INSERT(my_arr_t, &arr, 0, &i);
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
    for (i = 0; i < 5; i++) {
        int twenty = 20;
        printf("[INFO]: append 20\n");
        ret = ESI_ARR_APPEND(my_arr_t, &arr, &twenty);
        if (ret != 0) {
            printf("[ERROR]: append failed, check code\n");
        }
        printf("[INFO]: cap = %d, len = %d\n", ESI_ARR_CAP(my_arr_t, &arr), ESI_ARR_LEN(my_arr_t, &arr));
    }
    ESI_ARR_FOR_EACH_ELEM(my_arr_t, &arr, print_elem);
    if (ESI_ARR_CONTAINS(my_arr_t, &arr, &onehundred)) {
        printf("[ERROR]: contains fail, check code.\n");
    } {
        printf("[INFO]: array doesn't contain 100\n");
    }
    if (ESI_ARR_CONTAINS(my_arr_t, &arr, &three)) {
        printf("[INFO]: array contains 3\n");
    } else {
        printf("[ERROR]: contains fail, check code\n");
    }
    if (ESI_ARR_ANY(my_arr_t, &arr, predicate_gt15)) {
        printf("[INFO]: any greater than 15: yes\n");
    } else {
        printf("[ERROR]: check any implementation\n");
    }
    if (ESI_ARR_ANY(my_arr_t, &arr, predicate_lt0)) {
        printf("[ERROR]: check any implementation\n");
    } else {
        printf("[INFO]: any less than 0: no\n");
    }
    printf("[INFO]: the first index for 20 is %d\n", ESI_ARR_FIND_IF(my_arr_t, &arr, predicate_eq20));
    printf("[INFO]: the first index for 17 is %d\n", ESI_ARR_FIND_IF(my_arr_t, &arr, predicate_eq17));
    printf("[INFO]: everything is fine.\n");

    return 0;
}