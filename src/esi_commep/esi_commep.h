#pragma once 

/**
 * @file esi_commep.h
 * @brief interface for communication endpoint
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.08.09
*/

#include "esi_err/esi_err.h"

/**
 * commep is an interface not a class. 
 * wrap other concrete class or implementation to conform is interface.
 */
#define ESI_COMMEP_DECL(alias, unit_t, config_t) \
typedef unit_t alias##_unit_t;\
typedef confit_t alias##_config_t;\
struct alias##_commep {\
    void *blob;\
    esi_err_t (*send)(unit_t *, int, config_t *, int *);\
    esi_err_t (*recv)(unit_t *, int, config_t *, int *);\
    int (*poll)(confit_t *);\
};\
typedef struct alias##_commep alias;
