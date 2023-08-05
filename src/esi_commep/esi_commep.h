#pragma once 

/**
 * @file esi_commep.h
 * @brief interface for communication endpoint
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.07.26
*/

#include "esi_err/esi_err.h"

#define ESI_COMMEP_DECL(type_alias, unit_t, buffer_t) \
typedef unit_t type_alias##_unit_t;\
struct type_alias##_commep {\
    void *blob;\
    esi_err_t (*send)(buffer_t *, int *);\
    esi_err_t (*recv)(buffer_t *, int *);\
    int (*poll)(int);\
};