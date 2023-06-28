#pragma once 

/**
 * @file esi_ring.h
 * @brief "esi_ring.h" provides ring (circular queue) template
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.06.25
*/

enum esi_ring_err {
    ESI_RING_ERR_NONE = 0,
    ESI_RING_ERR_CAP = 1,
    ESI_RING_ERR_EMPTY = 2,
    ESI_RING_ERR_RANGE
};

#define ESI_RING_ERR_MSG {\
    "esi_ring: ok", /*0*/\
    "esi_ring: capacity has been reached", /*1*/\
    "esi_ring: empty", /*2*/\
    "esi_ring: index out of range" /*3*/\
}

const char *esi_ring_strerror(int err);

#define ESI_RING_TYPE_DECL(TYPE_ALIAS, ELEM_T, N) \
struct esi_ring_##ELEM_T##_##N {\
    ELEM_T data[N];\
    /* empty condition: head == tail; full condition: tail == (head - 1 + N) % N */\
    int head;\
    int tail;\
};\
typedef struct esi_ring_##ELEM_T##_##N esi_ring_##ELEM_T##_##N##_st;\
typedef esi_ring_##ELEM_T##_##N##_st* esi_ring_##ELEM_T##_##N##_st_ptr_t;\
typedef esi_ring_##ELEM_T##_##N##_st TYPE_ALIAS;\
typedef esi_ring_##ELEM_T##_##N##_st_ptr_t TYPE_ALIAS##_ptr_t;\
typedef ELEM_T esi_ring_##ELEM_T##_##N##_st_elem_t;\
typedef ELEM_T* esi_ring_##ELEM_T##_##N##_st_elem_ptr_t;\
typedef esi_ring_##ELEM_T##_##N##_st_elem_t TYPE_ALIAS##_elem_t;\
typedef esi_ring_##ELEM_T##_##N##_st_elem_ptr_t TYPE_ALIAS##_elem_ptr_t;\
int TYPE_ALIAS##_cap(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_len(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_is_empty(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_is_full(TYPE_ALIAS##_ptr_t);\
/* peek_front and peek_back will be provided by the form of macro */\
int TYPE_ALIAS##_push_back(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_elem_ptr_t);\
int TYPE_ALIAS##_push_front(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_elem_ptr_t);\
int TYPE_ALIAS##_pop_back(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_pop_front(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_find_if(TYPE_ALIAS##_ptr_t, int(*)(TYPE_ALIAS##_elem_ptr_t));\
int TYPE_ALIAS##_any(TYPE_ALIAS##_ptr_t, int(*)(TYPE_ALIAS##_elem_ptr_t));\
int TYPE_ALIAS##_contains(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_elem_ptr_t);\
void TYPE_ALIAS##_for_each_elem(TYPE_ALIAS##_ptr_t, void (*)(int, TYPE_ALIAS##_elem_ptr_t));\

#define ESI_RING_PTR_T(RING_T) RING_T##_ptr_t
#define ESI_RING_ELEM_T(RING_T) RING_T##_elem_t 
#define ESI_RING_ELEM_PTR_T(RING_T) RING_T##_elem_ptr_t

#define ESI_RING_DECL(RING_T, VAR) RING_T VAR = {.head = 0, .tail = 0}
#define ESI_RING_INIT(RING_T, VAR) VAR = {.head = 0, .tail = 0}
#define ESI_RING_INITIALIZER(RING_T) {.head = 0, .tail = 0}
#define ESI_RING_AT(RING_T, p_ring, pos) p_ring->data[(p_ring->head + pos) % RING_T##_cap(p_ring)]
#define ESI_RING_IS_EMPTY(RING_T, p_ring) RING_T##_is_empty(p_ring)
#define ESI_RING_IS_FULL(RING_T, p_ring) RING_T##_is_full(p_ring) 
#define ESI_RING_CAP(RING_T, p_ring) RING_T##_cap(p_ring)
#define ESI_RING_LEN(RING_T, p_ring) RING_T##_len(p_ring)
/* it's caller's responsibility to ensure peek is valid */
#define ESI_RING_PEEK_FRONT(RING_T, p_ring) (p_ring)->data[(p_ring)->head]
#define ESI_RING_PEEK_BACK(RING_T, p_ring) (p_ring)->data[((p_ring)->tail - 1 + RING_T##_cap(p_ring)) % RING_T##_cap(p_ring)]
#define ESI_RING_PUSH_FRONT(RING_T, p_ring, p_elem) RING_T##_push_front(p_ring, p_elem)
#define ESI_RING_PUSH_BACK(RING_T, p_ring, p_elem) RING_T##_push_back(p_ring, p_elem)
#define ESI_RING_POP_FRONT(RING_T, p_ring) RING_T##_pop_front(p_ring)
#define ESI_RING_POP_BACK(RING_T, p_ring) RING_T##_pop_back(p_ring)
#define ESI_RING_FIND_IF(RING_T, p_ring, predicate) RING_T##_find_if(p_ring, predicate)
#define ESI_RING_ANY(RING_T, p_ring, predicate) RING_T##_any(p_ring, predicate)
#define ESI_RING_CONTAINS(RING_T, p_ring, p_elem) RING_T##_contains(p_ring, p_elem)
#define ESI_RING_FOR_EACH_ELEM(RING_T, p_ring, func) RING_T##_for_each_elem(p_ring, func)

#define ESI_RING_TYPE_IMPL(TYPE_ALIAS, ELEM_T, N) \
int TYPE_ALIAS##_cap(TYPE_ALIAS##_ptr_t p_ring) {\
    return N;\
}\
int TYPE_ALIAS##_len(TYPE_ALIAS##_ptr_t p_ring) {\
    return (N + p_ring->tail - p_ring->head) % N;\
}\
int TYPE_ALIAS##_is_empty(TYPE_ALIAS##_ptr_t p_ring) {\
    return p_ring->head == p_ring->tail;\
}\
int TYPE_ALIAS##_is_full(TYPE_ALIAS##_ptr_t p_ring) {\
    return (p_ring->tail + 1) % N == p_ring->head;\
}\
int TYPE_ALIAS##_push_front(TYPE_ALIAS##_ptr_t p_ring, TYPE_ALIAS##_elem_ptr_t p_elem) {\
    if (TYPE_ALIAS##_is_full(p_ring)) {\
        return ESI_RING_ERR_CAP;\
    } else {\
        p_ring->head = (N + p_ring->head - 1) % N;\
        p_ring->data[p_ring->head] = *p_elem;\
    }\
    return ESI_RING_ERR_NONE;\
}\
int TYPE_ALIAS##_push_back(TYPE_ALIAS##_ptr_t p_ring, TYPE_ALIAS##_elem_ptr_t p_elem) {\
    if (TYPE_ALIAS##_is_full(p_ring)) {\
        return ESI_RING_ERR_CAP;\
    } else {\
        p_ring->data[p_ring->tail] = *p_elem;\
        p_ring->tail = (p_ring->tail + 1) % N;\
    }\
    return ESI_RING_ERR_NONE;\
}\
int TYPE_ALIAS##_pop_front(TYPE_ALIAS##_ptr_t p_ring) {\
    if (TYPE_ALIAS##_is_empty(p_ring)) {\
        return ESI_RING_ERR_EMPTY;\
    }\
    p_ring->head = (p_ring->head + 1) % N;\
    return ESI_RING_ERR_NONE;\
}\
int TYPE_ALIAS##_pop_back(TYPE_ALIAS##_ptr_t p_ring) {\
    if (TYPE_ALIAS##_is_empty(p_ring)) {\
        return ESI_RING_ERR_EMPTY;\
    }\
    p_ring->tail = (N + p_ring->tail - 1) % N;\
    return ESI_RING_ERR_NONE;\
}\
int TYPE_ALIAS##_find_if(TYPE_ALIAS##_ptr_t p_ring, int(*predicate)(TYPE_ALIAS##_elem_ptr_t)) {\
    int len = TYPE_ALIAS##_len(p_ring), i;\
    for (i = 0; i < len; i++) {\
        if (predicate(&(p_ring->data[(p_ring->head + i) % N])) != 0) {\
            return i;\
        }\
    }\
    return -1;\
}\
int TYPE_ALIAS##_any(TYPE_ALIAS##_ptr_t p_ring, int(*predicate)(TYPE_ALIAS##_elem_ptr_t)) {\
    int len = TYPE_ALIAS##_len(p_ring), i;\
    for (i = 0; i < len; i++) {\
        if (predicate(&(p_ring->data[(p_ring->head + i) % N])) != 0) {\
            return 1;\
        }\
    }\
    return 0;\
}\
int TYPE_ALIAS##_contains(TYPE_ALIAS##_ptr_t p_ring, TYPE_ALIAS##_elem_ptr_t p_elem) {\
    int len = TYPE_ALIAS##_len(p_ring), i;\
    for (i = 0; i < len; i++) {\
        if (p_ring->data[(p_ring->head + i) % N] == *p_elem) {\
            return 1;\
        }\
    }\
    return 0;\
}\
void TYPE_ALIAS##_for_each_elem(TYPE_ALIAS##_ptr_t p_ring, void (*func)(int, TYPE_ALIAS##_elem_ptr_t)) {\
    int len = TYPE_ALIAS##_len(p_ring), i;\
    for(i = 0; i < len; i++) {\
        func(i, &(p_ring->data[(p_ring->head + i) % N]));\
    }\
}

#define ESI_RING_TYPE_IMPL_WITH_EQ(TYPE_ALIAS, ELEM_T, N, EQ) \
int TYPE_ALIAS##_cap(TYPE_ALIAS##_ptr_t p_ring) {\
    return N;\
}\
int TYPE_ALIAS##_len(TYPE_ALIAS##_ptr_t p_ring) {\
    return (N + p_ring->tail - p_ring->head) % N;\
}\
int TYPE_ALIAS##_is_empty(TYPE_ALIAS##_ptr_t p_ring) {\
    return p_ring->head == p_ring->tail;\
}\
int TYPE_ALIAS##_is_full(TYPE_ALIAS##_ptr_t p_ring) {\
    return (p_ring->tail + 1) % N == p_ring->head;\
}\
int TYPE_ALIAS##_push_front(TYPE_ALIAS##_ptr_t p_ring, TYPE_ALIAS##_elem_ptr_t p_elem) {\
    if (TYPE_ALIAS##_is_full(p_ring)) {\
        return ESI_RING_ERR_CAP;\
    } else {\
        p_ring->head = (N + p_ring->head - 1) % N;\
        p_ring->data[p_ring->head] = *p_elem;\
    }\
    return ESI_RING_ERR_NONE;\
}\
int TYPE_ALIAS##_push_back(TYPE_ALIAS##_ptr_t p_ring, TYPE_ALIAS##_elem_ptr_t p_elem) {\
    if (TYPE_ALIAS##_is_full(p_ring)) {\
        return ESI_RING_ERR_CAP;\
    } else {\
        p_ring->data[p_ring->tail] = *p_elem;\
        p_ring->tail = (p_ring->tail + 1) % N;\
    }\
    return ESI_RING_ERR_NONE;\
}\
int TYPE_ALIAS##_pop_front(TYPE_ALIAS##_ptr_t p_ring) {\
    if (TYPE_ALIAS##_is_empty(p_ring)) {\
        return ESI_RING_ERR_EMPTY;\
    }\
    p_ring->head = (p_ring->head + 1) % N;\
    return ESI_RING_ERR_NONE;\
}\
int TYPE_ALIAS##_pop_back(TYPE_ALIAS##_ptr_t p_ring) {\
    if (TYPE_ALIAS##_is_empty(p_ring)) {\
        return ESI_RING_ERR_EMPTY;\
    }\
    p_ring->tail = (N + p_ring->tail - 1) % N;\
    return ESI_RING_ERR_NONE;\
}\
int TYPE_ALIAS##_find_if(TYPE_ALIAS##_ptr_t p_ring, int(*predicate)(TYPE_ALIAS##_elem_ptr_t)) {\
    int len = TYPE_ALIAS##_len(p_ring), i;\
    for (i = 0; i < len; i++) {\
        if (predicate(&(p_ring->data[(p_ring->head + i) % N])) != 0) {\
            return i;\
        }\
    }\
    return -1;\
}\
int TYPE_ALIAS##_any(TYPE_ALIAS##_ptr_t p_ring, int(*predicate)(TYPE_ALIAS##_elem_ptr_t)) {\
    int len = TYPE_ALIAS##_len(p_ring), i;\
    for (i = 0; i < len; i++) {\
        if (predicate(&(p_ring->data[(p_ring->head + i) % N])) != 0) {\
            return 1;\
        }\
    }\
    return 0;\
}\
int TYPE_ALIAS##_contains(TYPE_ALIAS##_ptr_t p_ring, TYPE_ALIAS##_elem_ptr_t p_elem) {\
    int len = TYPE_ALIAS##_len(p_ring), i;\
    for (i = 0; i < len; i++) {\
        if (EQ(&(p_ring->data[(p_ring->head + i) % N]), p_elem)) {\
            return 1;\
        }\
    }\
    return 0;\
}\
void TYPE_ALIAS##_for_each_elem(TYPE_ALIAS##_ptr_t p_ring, void (*func)(int, TYPE_ALIAS##_elem_ptr_t)) {\
    int len = TYPE_ALIAS##_len(p_ring), i;\
    for(i = 0; i < len; i++) {\
        func(i, &(p_ring->data[(p_ring->head + i) % N]));\
    }\
}