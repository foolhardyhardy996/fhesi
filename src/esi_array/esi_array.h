#pragma once 

/**
 * @file esi_arry.h
 * @brief refactor version for esi_arr
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.07.26
*/

#include "esi_err/esi_err.h"
#include "esi_functional/esi_functional.h"

/**
 * slice is an interface for accessing and manipulating array
*/
#define ESI_SLICE_ITF_DECL(alias, elem_t) \
typedef elem_t alias##_elem_t;\
struct alias##_slice_itf {\
    elem_t *array;\
    int cap;\
    int len;\
};\
typedef struct alias##_slice alias;\
elem_t *alias##_at(alias *, int);\
int alias##_index(alias *, elem_t *);\
int alias##_len(alias *);\
int alias##_cap(alias *);\
int alias##_isEmpty(alias *);\
int alias##_isFull(alias *);\
esi_err_t alias##_concat(alias *, alias *);\
esi_err_t alias##_concatWithAssign(alias *, alias *, ESI_ASSIGN_FUNC_T(elem_t, assign));\
esi_err_t alias##_insert(alias *, int, elem_t *);\
esi_err_t alias##_insertWithAssign(alias *, int, elem_t *, ESI_ASSIGN_FUNC_T(elem_t, assign));\
esi_err_t alias##_insertBack(alias *, elem_t *);\
esi_err_t alias##_insertBackWithAssign(alias *, elem_t *, ESI_ASSIGN_FUNC_T(elem_t, assign));\
esi_err_t alias##_delete(alias *, int);\
esi_err_t alias##_deleteWithAssign(alias *, int, ESI_ASSIGN_FUNC_T(elem_t, assign));\
esi_err_t alias##_deleteBack(alias *);\
esi_err_t alias##_emplace(alias *, int, ESI_MODIFY_FUNC_T(elem_t, emplace));\
esi_err_t alias##_emplaceBack(alias *, ESI_MODIFY_FUNC_T(elem_t, emplace));\
esi_err_t alias##_modify(alias *, int, ESI_MODIFY_FUNC_T(elem_t, modify));\
esi_err_t alias##_map(alias *, alias *, ESI_MAP_FUNC_T(elem_t, modify));\
esi_err_t alias##_copy(alias *, alias *);\
esi_err_t alias##_copyWithAssign(alias *, alias *, ESI_ASSIGN_FUNC_T(elem_t, assign));\
esi_err_t alias##_filter(alias *, alias *, ESI_PREDICATE_T(elem_t, predicate));\
esi_err_t alias##_filterWithAssign(alias *, alias *, ESI_PREDICATE_T(elem_t, predicate), ESI_ASSIGN_FUNC_T(elem_t, assign));\
esi_err_t alias##_foldLeft(alias *, void *, ESI_BIOP_FUNC_T(void, elem_t, void, biop));\
esi_err_t alias##_foldRight(alias *, void *, ESI_BIOP_FUNC_T(void, elem_t, void, biop));\
esi_err_t alias##_forEach(alias *, ESI_LITERAL_UNIOP_FUNC_T(elem_t *, void, op));\
int alias##_any(alias *, ESI_PREDICATE_T(elem_t, predicate));\
int alias##_all(alias *, ESI_PREDICATE_T(elem_t, predicate));\
elem_t *alias##_findWithPredicate(alias *, ESI_PREDICATE_T(elem_t, predicate));\
elem_t *alias##_findLastWithPredicate(alias *, ESI_PREDICATE_T(elem_t, predicate));\
int alias##_findIndexWithPredicate(alias *, ESI_PREDICATE_T(elem_t, predicate));\
int alias##_findLastIndexWithPredicate(alias *, ESI_PREDICATE_T(elem_t, predicate));\

#define ESI_SLICE_IMPL(type_alias, elem_t) \