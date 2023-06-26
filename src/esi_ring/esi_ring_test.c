#include <stdio.h>

#include "esi_ring.h"

ESI_RING_TYPE_DECL(my_ring_t, int, 16);
ESI_RING_TYPE_IMPL(my_ring_t, int, 16);

void print_elem(int index, int *val);

void print_elem(int index, int *val) {
    printf("ring[%d] = %d\n", index, *val);
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

int predicate_eq1(int *val);
int predicate_eq1(int *val) {
    return *val == 1;
}

int main(int argc, char *argv[]) {
    ESI_RING_DECL(my_ring_t, ring);
    ESI_RING_ELEM_T(my_ring_t) val = 10;
    ESI_RING_ELEM_PTR_T(my_ring_t) pval = &val;
    int i, ret;
    int onehundred = 100;
    int three = 3;
    printf("[INFO]: start testing\n");
    printf("[INFO]: cap = %d, len = %d\n", ESI_RING_CAP(my_ring_t, &ring), ESI_RING_LEN(my_ring_t, &ring));
    for(i = 0; i < 15; i++) {
        int j = -i;
        printf("[INFO]: push_back i = %d\n", i);
        ret = ESI_RING_PUSH_BACK(my_ring_t, &ring, &i);
        if (ret != 0) {
            printf("[ERROR]: push_back: %s\n", esi_ring_strerror(ret));
        }
        printf("[INFO]: push_front j = %d\n", j);
        ret = ESI_RING_PUSH_FRONT(my_ring_t, &ring, &j);
        if (ret != 0) {
            printf("[ERROR]: push_front: %s\n", esi_ring_strerror(ret));
        }
        printf("[INFO]: cap = %d, len = %d\n", ESI_RING_CAP(my_ring_t, &ring), ESI_RING_LEN(my_ring_t, &ring));
    }
    for(i = 0; i < 3; i++) {
        printf("[INFO]: pop_back pop_front i = %d\n", i);
        ret = ESI_RING_POP_BACK(my_ring_t, &ring);
        if (ret != 0) {
            printf("[ERROR]: pop_back: %s\n", esi_ring_strerror(ret));
        }
        ret = ESI_RING_POP_FRONT(my_ring_t, &ring);
        if (ret != 0) {
            printf("[ERROR]: pop_front: %s\n", esi_ring_strerror(ret));
        }
        printf("[INFO]: cap = %d, len = %d\n", ESI_RING_CAP(my_ring_t, &ring), ESI_RING_LEN(my_ring_t, &ring));
    }
    ESI_RING_FOR_EACH_ELEM(my_ring_t, &ring, print_elem);
    if (ESI_RING_CONTAINS(my_ring_t, &ring, &onehundred)) {
        printf("[ERROR]: contains fail, check code.\n");
    } {
        printf("[INFO]: ring doesn't contain 100\n");
    }
    if (ESI_RING_CONTAINS(my_ring_t, &ring, &three)) {
        printf("[INFO]: ring contains 3\n");
    } else {
        printf("[ERROR]: contains fail, check code\n");
    }
    if (ESI_RING_ANY(my_ring_t, &ring, predicate_gt15)) {
        printf("[INFO]: any greater than 15: yes\n");
    } else {
        printf("[ERROR]: check any implementation\n");
    }
    if (ESI_RING_ANY(my_ring_t, &ring, predicate_lt0)) {
        printf("[ERROR]: check any implementation\n");
    } else {
        printf("[INFO]: any less than 0: no\n");
    }
    printf("[INFO]: the first index for 20 is %d\n", ESI_RING_FIND_IF(my_ring_t, &ring, predicate_eq20));
    printf("[INFO]: the first index for 1 is %d\n", ESI_RING_FIND_IF(my_ring_t, &ring, predicate_eq1));
    printf("[INFO]: everything is fine.\n");

    return 0;
}