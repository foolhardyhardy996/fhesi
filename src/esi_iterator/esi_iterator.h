#pragma once 

/**
 * @file esi_iterator.h
 * @brief iterator interfaces and algorithms
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.07.26
*/

#include "esi_functional/esi_functional.h"

/**
 * iterator is an interface
*/
#define ESI_ITERATOR_DECL(type_alias, elem_t) \
struct type_alias##_iterator;\
typedef struct type_alias##_iterator type_alias;\
struct type_alias##_iterator {\
    void *blob;\
    elem_t *next(type_alias *);\
};\
esi_err_t type_alias##_forEach(type_alias *, ESI_LITERAL_UNIOP_FUNC_T(elem_t *, void, op));\
int type_alias##_any(type_alias *, ESI_PREDICATE_T(elem_t, predicate));\
int type_alias##_all(type_alias *, ESI_PREDICATE_T(elem_t, predicate));\
elem_t *type_alias##_findWithPredicate(type_alias *, ESI_PREDICATE_T(elem_t, predicate));\
