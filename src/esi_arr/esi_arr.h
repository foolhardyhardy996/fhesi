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
int TYPE_ALIAS##_is_empty(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_is_full(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_insert(TYPE_ALIAS##_ptr_t, int, TYPE_ALIAS##_elem_ptr_t);\
int TYPE_ALIAS##_append(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_elem_ptr_t);\
int TYPE_ALIAS##_remove(TYPE_ALIAS##_ptr_t, int);\
int TYPE_ALIAS##_find_if(TYPE_ALIAS##_ptr_t, int(*)(TYPE_ALIAS##_elem_ptr_t));\
int TYPE_ALIAS##_any(TYPE_ALIAS##_ptr_t, int(*)(TYPE_ALIAS##_elem_ptr_t));\
int TYPE_ALIAS##_contains(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_elem_ptr_t);\
void TYPE_ALIAS##_for_each_elem(TYPE_ALIAS##_ptr_t, void (*)(int, TYPE_ALIAS##_elem_ptr_t));\

#define ESI_ARR_PTR_T(ARR_T) ARR_T##_ptr_t
#define ESI_ARR_SLICE_T(ARR_T) ARR_T##_slice_t
#define ESI_ARR_ELEM_T(ARR_T) ARR_T##_elem_t 
#define ESI_ARR_ELEM_PTR_T(ARR_T) ARR_T##_elem_ptr_t

#define ESI_ARR_DECL(ARR_T, VAR) ARR_T VAR = {.size = 0}
#define ESI_ARR_INIT(ARR_T, VAR) VAR = {.size = 0}
#define ESI_ARR_INITIALIZER(ARR_T) {.size = 0}
#define ESI_ARR_AT(ARR_T, p_arr, pos) (p_arr)->data[pos]
#define ESI_ARR_IS_EMPTY(ARR_T, p_arr) ARR_T##_is_empty(p_arr)
#define ESI_ARR_IS_FULL(ARR_T, p_arr) ARR_T##_is_full(p_arr) 
#define ESI_ARR_CAP(ARR_T, p_arr) ARR_T##_cap(p_arr)
#define ESI_ARR_LEN(ARR_T, p_arr) ARR_T##_len(p_arr)
#define ESI_ARR_SLICE(ARR_T, p_arr, start, end) ARR_T##_slice(p_arr, start, end)
#define ESI_ARR_INSERT(ARR_T, p_arr, pos, p_elem) ARR_T##_insert(p_arr, pos, p_elem)
#define ESI_ARR_APPEND(ARR_T, p_arr, p_elem) ARR_T##_append(p_arr, p_elem)
#define ESI_ARR_REMOVE(ARR_T, p_arr, pos) ARR_T##_remove(p_arr, pos)
#define ESI_ARR_FIND_IF(ARR_T, p_arr, predicate) ARR_T##_find_if(p_arr, predicate)
#define ESI_ARR_ANY(ARR_T, p_arr, predicate) ARR_T##_any(p_arr, predicate)
#define ESI_ARR_CONTAINS(ARR_T, p_arr, p_elem) ARR_T##_contains(p_arr, p_elem)
#define ESI_ARR_FOR_EACH_ELEM(ARR_T, p_arr, func) ARR_T##_for_each_elem(p_arr, func)

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
int TYPE_ALIAS##_is_empty(TYPE_ALIAS##_ptr_t p_arr) {\
    if (p_arr->size == 0) {\
        return 1;\
    } else {\
        return 0;\
    } \
}\
int TYPE_ALIAS##_is_full(TYPE_ALIAS##_ptr_t p_arr) {\
    if (p_arr->size == N) {\
        return 1;\
    } else {\
        return 0;\
    }\
}\
int TYPE_ALIAS##_insert(TYPE_ALIAS##_ptr_t p_arr, int pos, TYPE_ALIAS##_elem_ptr_t p_elem) {\
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
        p_arr->data[pos] = *p_elem;\
        p_arr->size++;\
    }\
    return ESI_ARR_ERR_NONE;\
}\
int TYPE_ALIAS##_append(TYPE_ALIAS##_ptr_t p_arr, TYPE_ALIAS##_elem_ptr_t p_elem) {\
    return ESI_ARR_INSERT(TYPE_ALIAS, p_arr, ESI_ARR_LEN(TYPE_ALIAS, p_arr), p_elem);\
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
int TYPE_ALIAS##_find_if(TYPE_ALIAS##_ptr_t p_arr, int(*predicate)(TYPE_ALIAS##_elem_ptr_t)) {\
    int i = 0;\
    for (; i < p_arr->size; i++) {\
        if (predicate(&(p_arr->data[i])) != 0) {\
            return i;\
        }\
    }\
    return -1;\
}\
int TYPE_ALIAS##_any(TYPE_ALIAS##_ptr_t p_arr, int(*predicate)(TYPE_ALIAS##_elem_ptr_t)) {\
    int i = 0;\
    for (; i < p_arr->size; i++) {\
        if (predicate(&(p_arr->data[i])) != 0) {\
            return 1;\
        }\
    }\
    return 0;\
}\
int TYPE_ALIAS##_contains(TYPE_ALIAS##_ptr_t p_arr, TYPE_ALIAS##_elem_ptr_t p_elem) {\
    int i = 0;\
    for (; i < p_arr->size; i++) {\
        if (p_arr->data[i] == *p_elem) {\
            return 1;\
        }\
    }\
    return 0;\
}\
void TYPE_ALIAS##_for_each_elem(TYPE_ALIAS##_ptr_t p_arr, void (*func)(int, TYPE_ALIAS##_elem_ptr_t)) {\
    int i = 0;\
    for(; i < p_arr->size; i++) {\
        func(i, &(p_arr->data[i]));\
    }\
}

#define ESI_ARR_TYPE_IMPL_WITH_EQ(TYPE_ALIAS, ELEM_T, N, EQ) \
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
int TYPE_ALIAS##_is_empty(TYPE_ALIAS##_ptr_t p_arr) {\
    if (p_arr->size == 0) {\
        return 1;\
    } else {\
        return 0;\
    } \
}\
int TYPE_ALIAS##_is_full(TYPE_ALIAS##_ptr_t p_arr) {\
    if (p_arr->size == N) {\
        return 1;\
    } else {\
        return 0;\
    }\
}\
int TYPE_ALIAS##_insert(TYPE_ALIAS##_ptr_t p_arr, int pos, TYPE_ALIAS##_elem_ptr_t p_elem) {\
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
        p_arr->data[pos] = *p_elem;\
        p_arr->size++;\
    }\
    return ESI_ARR_ERR_NONE;\
}\
int TYPE_ALIAS##_append(TYPE_ALIAS##_ptr_t p_arr, TYPE_ALIAS##_elem_ptr_t p_elem) {\
    return ESI_ARR_INSERT(TYPE_ALIAS, p_arr, ESI_ARR_LEN(TYPE_ALIAS, p_arr), p_elem);\
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
int TYPE_ALIAS##_find_if(TYPE_ALIAS##_ptr_t p_arr, int(*predicate)(TYPE_ALIAS##_elem_ptr_t)) {\
    int i = 0;\
    for (; i < p_arr->size; i++) {\
        if (predicate(&(p_arr->data[i])) != 0) {\
            return i;\
        }\
    }\
    return -1;\
}\
int TYPE_ALIAS##_any(TYPE_ALIAS##_ptr_t p_arr, int(*predicate)(TYPE_ALIAS##_elem_ptr_t)) {\
    int i = 0;\
    for (; i < p_arr->size; i++) {\
        if (predicate(&(p_arr->data[i])) != 0) {\
            return 1;\
        }\
    }\
    return 0;\
}\
int TYPE_ALIAS##_contains(TYPE_ALIAS##_ptr_t p_arr, TYPE_ALIAS##_elem_ptr_t p_elem) {\
    int i = 0;\
    for (; i < p_arr->size; i++) {\
        if (EQ(&(p_arr->data[i]), p_elem)) {\
            return 1;\
        }\
    }\
    return 0;\
}\
void TYPE_ALIAS##_for_each_elem(TYPE_ALIAS##_ptr_t p_arr, void (*func)(int, TYPE_ALIAS##_elem_ptr_t)) {\
    int i = 0;\
    for(; i < p_arr->size; i++) {\
        func(i, &(p_arr->data[i]));\
    }\
}