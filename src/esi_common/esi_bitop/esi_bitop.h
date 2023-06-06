#pragma once 

/**
 * @file esi_bitop.h 
 * @brief "esi_bitop" provides common bit operations.
 * 
 * 
 * 
 * @author Li Weida (adaptor), hans-jorg (original author)
 * @date 2023.06.06
*/

#define ESI_BITOP_BIT(N)                      (1UL<<(N))
// Bit manipulation using masks
#define ESI_BITOP_MASKSET(V,M)                 (V)|=(M)
#define ESI_BITOP_MASKCLEAR(V,M)               (V)&=~(M)
#define ESI_BITOP_MASKTOGGLE(V,M)              (V)^=(M)
// Bit manipulation using indexes
#define ESI_BITOP_BITSET(V,N)                 (V)|=ESI_BITOP_BIT(N)
#define ESI_BITOP_BITCLEAR(V,N)               (V)&=~ESI_BITOP_BIT(N)
#define ESI_BITOP_BITTOGGLE(V,N)              (V)^=ESI_BITOP_BIT(N)
