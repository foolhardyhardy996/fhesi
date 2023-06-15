#pragma once 

/**
 * @file esi_arr.h
 * @brief "esi_arr.h" provides array template
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.06.15
*/

/**
 * Assumption: ELEM_T is primitive type or aggregate type
*/

enum esi_arr_err {
    ESI_ARR_ERR_NONE = 0,
    ESI_ARR_ERR_CAP = 1,
    ESI_ARR_ERR_EMPTY = 2,
    ESI_ARR_ERR_RANGE
};

#define ESI_ARR_ERR_MSG {\
    "esi_arr: ok", /*0*/\
    "esi_arr: capacity has been reached", /*1*/\
    "esi_arr: empty", /*2*/\
    "esi_arr: index out of range" /*3*/\
}

const char *esi_arr_strerror(int err);

#define ESI_ARR_TYPE_DECL(TYPE_ALIAS, ELEM_T, N) \
struct esi_arr_##ELEM_T##_##N {\
    ELEM_T data[N];\
    int size;\
};\
struct esi_slice_##ELEM_T##_##N {\
    ELEM_T *data;\
    int size;\
};\
typedef struct esi_arr_##ELEM_T##_##N esi_arr_##ELEM_T##_##N##_st;\
typedef struct esi_slice_##ELEM_T##_##N esi_slice_##ELEM_T##_##N##_st;\
typedef esi_arr_##ELEM_T##_##N##_st* esi_arr_##ELEM_T##_##N##_st_ptr_t;\
typedef ELEM_T esi_arr_##ELEM_T##_##N##_st_elem_t;\
typedef ELEM_T* esi_arr_##ELEM_T##_##N##_st_elem_ptr_t;\
typedef esi_arr_##ELEM_T##_##N##_st TYPE_ALIAS;\
typedef esi_slice_##ELEM_T##_##N##_st TYPE_ALIAS##_slice_t;\
typedef esi_arr_##ELEM_T##_##N##_st_ptr_t TYPE_ALIAS##_ptr_t;\
typedef esi_arr_##ELEM_T##_##N##_st_elem_t TYPE_ALIAS##_elem_t;\
typedef esi_arr_##ELEM_T##_##N##_st_elem_ptr_t TYPE_ALIAS##_elem_ptr_t;\
int TYPE_ALIAS##_cap(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_len(TYPE_ALIAS##_ptr_t);\
TYPE_ALIAS##_slice_t TYPE_ALIAS##_slice(TYPE_ALIAS##_ptr_t, int, int);\
int TYPE_ALIAS##_insert(TYPE_ALIAS##_ptr_t, int, ELEM_T);\
int TYPE_ALIAS##_remove(TYPE_ALIAS##_ptr_t, int);\
void TYPE_ALIAS##_for_each_elem(TYPE_ALIAS##_ptr_t, void (*)(int, ELEM_T));\

#define ESI_ARR_TYPE_IMPL(TYPE_ALIAS, ELEM_T, N) \
int TYPE_ALIAS##_cap(TYPE_ALIAS##_ptr_t p_arr) {\
    return N;\
}\
int TYPE_ALIAS##_len(TYPE_ALIAS##_ptr_t p_arr) {\
    return p_arr->size;\
}\
TYPE_ALIAS##_slice_t TYPE_ALIAS##_slice(TYPE_ALIAS##_ptr_t p_arr, int start, int end) {\
    TYPE_ALIAS##_slice_t slice = {p_arr->data + start, end - start};\
    return slice;\
}\
int TYPE_ALIAS##_insert(TYPE_ALIAS##_ptr_t p_arr, int pos, ELEM_T elem) {\
    if (p_arr->size >= N) {\
        return ESI_ARR_ERR_CAP;\
    }\
    if (pos > p_arr->size) {\
        return ESI_ARR_ERR_RANGE;\
    } else {\
        int i;\
        for (i = p_arr->size; i > pos; i--) {\
            p_arr->data[i] = p_arr->data[i-1];\
        }\
        p_arr->data[pos] = elem;\
        p_arr->size++;\
    }\
    return ESI_ARR_ERR_NONE;\
}\
int TYPE_ALIAS##_remove(TYPE_ALIAS##_ptr_t p_arr, int pos) {\
    if (p_arr->size == 0) {\
        return ESI_ARR_ERR_EMPTY;\
    }\
    if (pos >= p_arr->size) {\
        return ESI_ARR_ERR_RANGE;\
    } else {\
        for(; pos < p_arr->size - 1; pos++) {\
            p_arr->data[pos] = p_arr->data[pos+1];\
        }\
        p_arr->size--;\
    }\
    return ESI_ARR_ERR_NONE;\
}\
void TYPE_ALIAS##_for_each_elem(TYPE_ALIAS##_ptr_t p_arr, void (*func)(int, ELEM_T)) {\
    int i = 0;\
    for(; i < p_arr->size; i++) {\
        func(i, p_arr->data[i]);\
    }\
}

#define ESI_ARR_PTR_T(ARR_T) ARR_T##_ptr_t
#define ESI_ARR_SLICE_T(ARR_T) ARR_T##_slice_t
#define ESI_ARR_ELEM_T(ARR_T) ARR_T##_elem_t 
#define ESI_ARR_ELEM_PTR_T(ARR_T) ARR_T##_elem_ptr_t

#define ESI_ARR_DECL(ARR_T, VAR) ARR_T VAR = {.size = 0}
#define ESI_ARR_INIT(ARR_t, VAR) VAR = {.size = 0}
#define ESI_ARR_CAP(ARR_T, p_arr) ARR_T##_cap(p_arr)
#define ESI_ARR_LEN(ARR_T, p_arr) ARR_T##_len(p_arr)
#define ESI_ARR_SLICE(ARR_T, p_arr, start, end) ARR_T##_slice(p_arr, start, end)
#define ESI_ARR_INSERT(ARR_T, p_arr, pos, elem) ARR_T##_insert(p_arr, pos, elem)
#define ESI_ARR_REMOVE(ARR_T, p_arr, pos) ARR_T##_remove(p_arr, pos)
#define ESI_ARR_FOR_EACH_ELEM(ARR_T, p_arr, func) ARR_T##_for_each_elem(p_arr, func)
