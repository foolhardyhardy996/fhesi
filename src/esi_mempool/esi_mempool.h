#pragma once 

/**
 * @file esi_mempool.h
 * @brief "esi_mempool" provide a fixed-size memory block pool implementation.
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.06.07
*/

struct mempool {
    void *base;
    int size;
    int block_size;
    int alignment;

    void *aligned_base;
    int usable_size;
    int aligned_block_size;
    int block_num;
    int mask[block_num/sizeof(int)];
};

#define ESI_MEMPOOL_DECLARE(NAME, BASE, ALIGNMENT, SIZE, BLOCKSZ, ) \
struct esi_mempool_#NAME {\
    void *base;\
    int alignment;\
    int size;\
    int block_size;\
    \
    void *aligned_base;\
    int usable_size;\
    int aligned_block_size;\
    int block_num;\
    int mask[()/()]
};