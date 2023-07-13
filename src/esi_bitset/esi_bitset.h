#pragma once 

/**
 * @file esi_bitset.h
 * @brief "esi_bitset" provides bitset implementation.
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.06.07
*/

#include "esi_common/esi_bitop/esi_bitop.h"

struct esi_bitset_descriptor {
    int bit_num;
    int holder_len;
};

struct esi_bitset {
    struct esi_bitset_descriptor descriptor;
    int *holder;
};

/**
 * @brief declare a bitset variable.
 * 
 * BITNUM should be a constant.
*/
#define ESI_BITSET_STATIC_DECLARE(BITNUM, VAR) \
static int esi_bitset_holder_for_##VAR[(int)((BITNUM)/sizeof(int)) + 1] = {0};
struct esi_bitset VAR = {\
    {
        (BITNUM),\
        (BITNUM)/sizeof(int) + 1\
    },\
    esi_bitset_holder_for_##VAR\
};

int esi_bitset_set(esi_bitset *bitset, int pos);
int esi_bitset_get(int pos);
int esi_bitset_toggle(int pos);
int esi_bitset_get_lowest_on_bit()

#define esi_bitset_set(bs, pos) \
(ESI_BITOP_BITSET((bs)->holder[(pos) / sizeof(int)], (pos) % sizeof(int)))

#define esi_bitset_clear(bs, pos) \
(ESI_BITOP_BITCLEAR((bs)->holder[(pos) / sizeof(int)], (pos) % sizeof(int)))

#define esi_bitset_toggle(bs, pos) \
(ESI_BITOP_BITTOGGLE((bs)->holder[(pos) / sizeof(int)], (pos) % sizeof(int)))

#define esi_bitset_is_on(bs, pos) \
(ESI_BITOP_IS_ON((bs)->holder[(pos) / sizeof(int)], (pos) % sizeof(int)))

int esi_bitset_get_lowest_on_bit_pos(struct esi_bitset *bs);