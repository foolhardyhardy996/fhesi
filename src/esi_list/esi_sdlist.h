#pragma once 

/**
 * @file esi_sdlist.h
 * @brief "esi_sdlist.h" provides templates for static doubly linked list.
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.06.29
*/

enum esi_sdlist_err {
    ESI_SDLIST_ERR_NONE = 0,
    ESI_SDLIST_ERR_CAP = 1,
    ESI_SDLIST_ERR_EMPTY = 2,
    ESI_SDLIST_ERR_INVALID_NODE = 3
};

#define ESI_SDLIST_ERR_MSG {\
    "esi_sdlist: ok", /*0*/\
    "esi_sdlist: capacity has been reached", /*1*/\
    "esi_sdlist: empty", /*2*/\
    "esi_sdlist: invalid node" /*3*/\
}

const char *esi_sdlist_strerror(int err);

#define ESI_SDLIST_TYPE_DECL(TYPE_ALIAS, NODE_DATA_T, N) \
typedef NODE_DATA_T TYPE_ALIAS##_node_data_t;\
typedef NODE_DATA_T *TYPE_ALIAS##_node_data_ptr_t;\
struct esi_sdlist_node_##TYPE_ALIAS {\
    int prev;\
    int next;\
    NODE_DATA_T node_data;\
};\
typedef struct esi_sdlist_node_##TYPE_ALIAS TYPE_ALIAS##_node_t;\
typedef TYPE_ALIAS##_node_t *TYPE_ALIAS##_node_ptr_t;\
struct esi_sdlist_##TYPE_ALIAS {\
    TYPE_ALIAS##_node_t node_repo[N];\
    int list_head;\
    int list_tail;\
    int free_list_head;\
};\
typedef struct esi_sdlist_##TYPE_ALIAS TYPE_ALIAS;\
typedef TYPE_ALIAS *TYPE_ALIAS##_ptr_t;\
int TYPE_ALIAS##_init(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_cap(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_len(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_get_free_list_len(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_is_empty(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_is_full(TYPE_ALIAS##_ptr_t);\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_get_next_node(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_node_ptr_t);\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_get_prev_node(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_node_ptr_t);\
int TYPE_ALIAS##_get_node_index(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_node_ptr_t);\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_find_next_if(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_node_ptr_t, int(*)(NODE_DATA_T *));\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_find_if(TYPE_ALIAS##_ptr_t, int(*)(NODE_DATA_T *));\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_peek_front(TYPE_ALIAS##_ptr_t);\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_peek_back(TYPE_ALIAS##_ptr_t);\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_alloc_node(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_free_node(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_node_ptr_t);\
int TYPE_ALIAS##_insert_after(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_node_ptr_t, NODE_DATA_T *);\
int TYPE_ALIAS##_insert_before(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_node_ptr_t, NODE_DATA_T *);\
int TYPE_ALIAS##_push_front(TYPE_ALIAS##_ptr_t, NODE_DATA_T *);\
int TYPE_ALIAS##_push_back(TYPE_ALIAS##_ptr_t, NODE_DATA_T *);\
int TYPE_ALIAS##_delete(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_node_ptr_t);\
int TYPE_ALIAS##_pop_front(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_pop_back(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_any_if(TYPE_ALIAS##_ptr_t, int(*)(NODE_DATA_T *));\
void TYPE_ALIAS##_for_each(TYPE_ALIAS##_ptr_t, void(*)(NODE_DATA_T *));\

#define ESI_SDLIST_NODE_T(SDLIST_T) SDLIST_T##_node_t 
#define ESI_SDLIST_NODE_DATA_T(SDLIST_T) SDLIST_T##_node_data_t

#define ESI_SDLIST_INIT(SDLIST_T, p_sdlist) SDLIST_T##_init(p_sdlist)
#define ESI_SDLIST_CAP(SDLIST_T, p_sdlist) SDLIST_T##_cap(p_sdlist)
#define ESI_SDLIST_LEN(SDLIST_T, p_sdlist) SDLIST_T##_len(p_sdlist)
#define ESI_SDLIST_GET_FREE_LIST_LEN(SDLIST_T, p_sdlist) SDLIST_T##_get_free_list_len(p_sdlist)
#define ESI_SDLIST_IS_EMPTY(SDLIST_T, p_sdlist) SDLIST_T##_is_empty(p_sdlist)
#define ESI_SDLIST_IS_FULL(SDLIST_T, p_sdlist) SDLIST_T##_is_full(p_sdlist)
#define ESI_SDLIST_GET_NEXT_NODE(SDLIST_T, p_sdlist, p_node) SDLIST_T##_get_next_node(p_sdlist, p_node)
#define ESI_SDLIST_GET_PREV_NODE(SDLIST_T, p_sdlist, p_node) SDLIST_T##_get_prev_node(p_sdlist, p_node)
#define ESI_SDLIST_GET_NODE_INDEX(SDLIST_T, p_sdlist, p_node) SDLIST_T##_get_node_index(p_sdlist, p_node)
#define ESI_SDLIST_FIND_NEXT_IF(SDLIST_T, p_sdlist, p_node, predicate) SDLIST_T##_find_next_if(p_sdlist, p_node, predicate)
#define ESI_SDLIST_FIND_IF(SDLIST_T, p_sdlist, predicate) SDLIST_T##_find_if(p_sdlist, predicate)
#define ESI_SDLIST_PEEK_FRONT(SDLIST_T, p_sdlist) SDLIST_T##_peek_front(p_sdlist)
#define ESI_SDLIST_PEEK_BACK(SDLIST_T, p_sdlist) SDLIST_T##_peek_back(p_sdlist)
#define ESI_SDLIST_ALLOC_NODE(SDLIST_T, p_sdlist) SDLIST_T##_alloc_node(p_sdlist)
#define ESI_SDLIST_FREE_NODE(SDLIST_T, p_sdlist, p_node) SDLIST_T##_free_node(p_sdlist, p_node)
#define ESI_SDLIST_INSERT_AFTER(SDLIST_T, p_sdlist, p_node, p_node_data) SDLIST_T##_insert_after(p_sdlist, p_node, p_node_data)
#define ESI_SDLIST_INSERT_BEFORE(SDLIST_T, p_sdlist, p_node, p_node_data) SDLIST_T##_insert_before(p_sdlist, p_node, p_node_data)
#define ESI_SDLIST_PUSH_FRONT(SDLIST_T, p_sdlist, p_node_data) SDLIST_T##_push_front(p_sdlist, p_node_data)
#define ESI_SDLIST_PUSH_BACK(SDLIST_T, p_sdlist, p_node_data) SDLIST_T##_push_back(p_sdlist, p_node_data)
#define ESI_SDLIST_DELETE(SDLIST_T, p_sdlist, p_node) SDLIST_T##_delete(p_sdlist, p_node)
#define ESI_SDLIST_POP_FRONT(SDLIST_T, p_sdlist) SDLIST_T##_pop_front(p_sdlist)
#define ESI_SDLIST_POP_BACK(SDLIST_T, p_sdlist) SDLIST_T##_pop_back(p_sdlist)
#define ESI_SDLIST_ANY_IF(SDLIST_T, p_sdlist, predicate) SDLIST_T##_any_if(p_sdlist, predicate)
#define ESI_SDLIST_FOR_EACH(SDLIST_T, p_sdlist, func) SDLIST_T##_for_each(p_sdlist, func)

#define ESI_SDLIST_TYPE_IMPL(TYPE_ALIAS, NODE_DATA_T, N) \
int TYPE_ALIAS##_init(TYPE_ALIAS##_ptr_t p_sdlist) {\
    int i;\
    TYPE_ALIAS##_node_t *p_node;\
    p_sdlist->list_head = -1;\
    p_sdlist->list_tail = -1;\
    p_sdlist->free_list_head = 0;\
    for (i = 0; i < N; i++) {\
        p_node = &(p_sdlist->node_repo[i]);\
        if (i == 0) {\
            p_node->prev = -1;\
        } else {\
            p_node->prev = i - 1;\
        }\
        if (i == (N) - 1) {\
            p_node->next = -1;\
        } else {\
            p_node->next = i + 1;\
        }\
    }\
    return ESI_SDLIST_ERR_NONE;\
}\
int TYPE_ALIAS##_cap(TYPE_ALIAS##_ptr_t p_sdlist) {\
    return N;\
}\
int TYPE_ALIAS##_len(TYPE_ALIAS##_ptr_t p_sdlist) {\
    int len = 0;\
    int index = p_sdlist->list_head;\
    while (index != -1) {\
        len++;\
        index = p_sdlist->node_repo[index].next;\
    }\
    return len;\
}\
int TYPE_ALIAS##_get_free_list_len(TYPE_ALIAS##_ptr_t p_sdlist) {\
    int len = 0;\
    int index = p_sdlist->free_list_head;\
    while (index != -1) {\
        len++;\
        index = p_sdlist->node_repo[index].next;\
    }\
    return len;\
}\
int TYPE_ALIAS##_is_empty(TYPE_ALIAS##_ptr_t p_sdlist) {\
    return p_sdlist->list_head == -1;\
}\
int TYPE_ALIAS##_is_full(TYPE_ALIAS##_ptr_t p_sdlist) {\
    return p_sdlist->free_list_head == -1;\
}\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_get_next_node(TYPE_ALIAS##_ptr_t p_sdlist, TYPE_ALIAS##_node_ptr_t p_node) {\
    if (p_node->next != -1) {\
        return &(p_sdlist->node_repo[p_node->next]);\
    } else {\
        return NULL;\
    }\
}\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_get_prev_node(TYPE_ALIAS##_ptr_t p_sdlist, TYPE_ALIAS##_node_ptr_t p_node) {\
    if (p_node->prev != -1) {\
        return &(p_sdlist->node_repo[p_node->prev]);\
    } else {\
        return NULL;\
    }\
}\
int TYPE_ALIAS##_get_node_index(TYPE_ALIAS##_ptr_t p_sdlist, TYPE_ALIAS##_node_ptr_t p_node) {\
    int index = p_node - &(p_sdlist->node_repo[0]);\
    if (index >= N || index < 0) {\
        return -1;\
    }\
    return index;\
}\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_find_next_if(TYPE_ALIAS##_ptr_t p_sdlist, TYPE_ALIAS##_node_ptr_t p_start_node, int(*predicate)(NODE_DATA_T *)) {\
    TYPE_ALIAS##_node_ptr_t p_node = p_start_node;\
    while (p_node != NULL) {\
        if (predicate(&(p_node->node_data))) {\
            return p_node;\
        }\
        p_node = TYPE_ALIAS##_get_next_node(p_sdlist, p_node);\
    }\
    return NULL;\
}\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_find_if(TYPE_ALIAS##_ptr_t p_sdlist, int(*predicate)(NODE_DATA_T *)) {\
    TYPE_ALIAS##_node_ptr_t p_node = TYPE_ALIAS##_peek_front(p_sdlist);\
    if (p_node != NULL) {\
        return TYPE_ALIAS##_find_next_if(p_sdlist, p_node, predicate);\
    }\
    return NULL;\
}\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_peek_front(TYPE_ALIAS##_ptr_t p_sdlist) {\
    if (p_sdlist->list_head == -1) {\
        return NULL;\
    } else {\
        return &(p_sdlist->node_repo[p_sdlist->list_head]);\
    }\
}\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_peek_back(TYPE_ALIAS##_ptr_t p_sdlist) {\
    if (p_sdlist->list_tail == -1) {\
        return NULL;\
    } else {\
        return &(p_sdlist->node_repo[p_sdlist->list_tail]);\
    }\
}\
TYPE_ALIAS##_node_ptr_t TYPE_ALIAS##_alloc_node(TYPE_ALIAS##_ptr_t p_sdlist) {\
    TYPE_ALIAS##_node_ptr_t p_pivot, p_pivot_next;\
    if (p_sdlist->free_list_head == -1) {\
        return NULL;\
    }\
    p_pivot = &(p_sdlist->node_repo[p_sdlist->free_list_head]);\
    p_sdlist->free_list_head = p_pivot->next;\
    if (p_pivot->next != -1) {\
        p_pivot_next = &(p_sdlist->node_repo[p_pivot->next]);\
        p_pivot_next->prev = -1;\
    }\
    return p_pivot;\
}\
int TYPE_ALIAS##_free_node(TYPE_ALIAS##_ptr_t p_sdlist, TYPE_ALIAS##_node_ptr_t p_node) {\
    TYPE_ALIAS##_node_ptr_t p_pivot, p_pivot_next;\
    int pivot_index;\
    if (p_node != NULL) {\
        p_pivot = p_node;\
    } else {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    }\
    pivot_index = TYPE_ALIAS##_get_node_index(p_sdlist, p_node);\
    if (pivot_index == -1) {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    }\
    if (p_sdlist->free_list_head != -1) {\
        p_pivot_next = &(p_sdlist->node_repo[p_sdlist->free_list_head]);\
        p_pivot_next->prev = pivot_index;\
    }\
    p_pivot->next = p_sdlist->free_list_head;\
    p_pivot->prev = -1;\
    p_sdlist->free_list_head = pivot_index;\
    return ESI_SDLIST_ERR_NONE;\
}\
int TYPE_ALIAS##_insert_after(TYPE_ALIAS##_ptr_t p_sdlist, TYPE_ALIAS##_node_ptr_t p_node, NODE_DATA_T *p_node_data) {\
    TYPE_ALIAS##_node_ptr_t p_pivot, p_pivot_prev, p_pivot_next;\
    int pivot_index, pivot_prev_index, pivot_next_index;\
    if (TYPE_ALIAS##_is_full(p_sdlist)) {\
        return ESI_SDLIST_ERR_CAP;\
    }\
    p_pivot_prev = p_node;\
    pivot_prev_index = TYPE_ALIAS##_get_node_index(p_sdlist, p_pivot_prev);\
    if (pivot_prev_index == -1) {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    }\
    pivot_next_index = p_pivot_prev->next;\
    p_pivot = TYPE_ALIAS##_alloc_node(p_sdlist);\
    pivot_index = TYPE_ALIAS##_get_node_index(p_sdlist, p_pivot);\
    p_pivot->node_data = *p_node_data;\
    p_pivot->next = pivot_next_index;\
    p_pivot->prev = pivot_prev_index;\
    p_pivot_prev->next = pivot_index;\
    if (pivot_next_index != -1) {\
        p_pivot_next = &(p_sdlist->node_repo[pivot_next_index]);\
        p_pivot_next->prev = pivot_index;\
    } else {\
        p_pivot_next = NULL;\
        p_sdlist->list_tail = pivot_index;\
    }\
    return ESI_SDLIST_ERR_NONE;\
}\
int TYPE_ALIAS##_insert_before(TYPE_ALIAS##_ptr_t p_sdlist, TYPE_ALIAS##_node_ptr_t p_node, NODE_DATA_T *p_node_data) {\
    TYPE_ALIAS##_node_ptr_t p_pivot, p_pivot_prev, p_pivot_next;\
    int pivot_index, pivot_prev_index, pivot_next_index;\
    if (TYPE_ALIAS##_is_full(p_sdlist)) {\
        return ESI_SDLIST_ERR_CAP;\
    }\
    p_pivot_next = p_node;\
    pivot_next_index = TYPE_ALIAS##_get_node_index(p_sdlist, p_pivot_next);\
    if (pivot_next_index == -1) {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    }\
    pivot_prev_index = p_pivot_next->prev;\
    p_pivot = TYPE_ALIAS##_alloc_node(p_sdlist);\
    pivot_index = TYPE_ALIAS##_get_node_index(p_sdlist, p_pivot);\
    p_pivot->node_data = *p_node_data;\
    p_pivot->next = pivot_next_index;\
    p_pivot->prev = pivot_prev_index;\
    p_pivot_next->prev = pivot_index;\
    if (pivot_prev_index != -1) {\
        p_pivot_prev = &(p_sdlist->node_repo[pivot_prev_index]);\
        p_pivot_prev->next = pivot_index;\
    } else {\
        p_pivot_prev = NULL;\
        p_sdlist->list_head = pivot_index;\
    }\
    return ESI_SDLIST_ERR_NONE;\
}\
int TYPE_ALIAS##_push_front(TYPE_ALIAS##_ptr_t p_sdlist, NODE_DATA_T *p_node_data) {\
    TYPE_ALIAS##_node_ptr_t p_pivot, p_pivot_next;\
    int pivot_index, pivot_next_index;\
    if (TYPE_ALIAS##_is_full(p_sdlist)) {\
        return ESI_SDLIST_ERR_CAP;\
    }\
    p_pivot = TYPE_ALIAS##_alloc_node(p_sdlist);\
    pivot_index = TYPE_ALIAS##_get_node_index(p_sdlist, p_pivot);\
    if (TYPE_ALIAS##_is_empty(p_sdlist)) {\
        p_pivot->prev = -1;\
        p_pivot->next = -1;\
        p_pivot->node_data = *p_node_data;\
        p_sdlist->list_head = pivot_index;\
        p_sdlist->list_tail = pivot_index;\
    } else {\
        pivot_next_index = p_sdlist->list_head;\
        p_pivot_next = &(p_sdlist->node_repo[pivot_next_index]);\
        p_pivot_next->prev = pivot_index;\
        p_pivot->prev = -1;\
        p_pivot->next = pivot_next_index;\
        p_pivot->node_data = *p_node_data;\
        p_sdlist->list_head = pivot_index;\
    }\
    return ESI_SDLIST_ERR_NONE;\
}\
int TYPE_ALIAS##_push_back(TYPE_ALIAS##_ptr_t p_sdlist, NODE_DATA_T *p_node_data) {\
    TYPE_ALIAS##_node_ptr_t p_pivot, p_pivot_prev;\
    int pivot_index, pivot_prev_index;\
    if (TYPE_ALIAS##_is_full(p_sdlist)) {\
        return ESI_SDLIST_ERR_CAP;\
    }\
    p_pivot = TYPE_ALIAS##_alloc_node(p_sdlist);\
    pivot_index = TYPE_ALIAS##_get_node_index(p_sdlist, p_pivot);\
    if (TYPE_ALIAS##_is_empty(p_sdlist)) {\
        p_pivot->prev = -1;\
        p_pivot->next = -1;\
        p_pivot->node_data = *p_node_data;\
        p_sdlist->list_head = pivot_index;\
        p_sdlist->list_tail = pivot_index;\
    } else {\
        pivot_prev_index = p_sdlist->list_tail;\
        p_pivot_prev = &(p_sdlist->node_repo[pivot_prev_index]);\
        p_pivot_prev->next = pivot_index;\
        p_pivot->prev = pivot_prev_index;\
        p_pivot->next = -1;\
        p_pivot->node_data = *p_node_data;\
        p_sdlist->list_tail = pivot_index;\
    }\
    return ESI_SDLIST_ERR_NONE;\
}\
int TYPE_ALIAS##_delete(TYPE_ALIAS##_ptr_t p_sdlist, TYPE_ALIAS##_node_ptr_t p_node) {\
    TYPE_ALIAS##_node_ptr_t p_pivot, p_pivot_prev, p_pivot_next;\
    int pivot_index, pivot_prev_index, pivot_next_index;\
    if (p_node == NULL) {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    } else {\
        p_pivot = p_node;\
        pivot_index = TYPE_ALIAS##_get_node_index(p_sdlist, p_pivot);\
        if (pivot_index == -1) {\
            return ESI_SDLIST_ERR_INVALID_NODE;\
        }\
    }\
    pivot_prev_index = p_pivot->prev;\
    pivot_next_index = p_pivot->next;\
    if (pivot_prev_index != -1) {\
        p_pivot_prev = &(p_sdlist->node_repo[pivot_prev_index]);\
        p_pivot_prev->next = pivot_next_index;\
    } else {\
        p_sdlist->list_head = pivot_next_index;\
    }\
    if (pivot_next_index != -1) {\
        p_pivot_next = &(p_sdlist->node_repo[pivot_next_index]);\
        p_pivot_next->prev = pivot_prev_index;\
    } else {\
        p_sdlist->list_tail = pivot_prev_index;\
    }\
    TYPE_ALIAS##_free_node(p_sdlist, p_pivot);\
    return ESI_SDLIST_ERR_NONE;\
}\
int TYPE_ALIAS##_pop_front(TYPE_ALIAS##_ptr_t p_sdlist) {\
    if (TYPE_ALIAS##_is_empty(p_sdlist)) {\
        return ESI_SDLIST_ERR_NONE;\
    }\
    return TYPE_ALIAS##_delete(p_sdlist, TYPE_ALIAS##_peek_front(p_sdlist));\
}\
int TYPE_ALIAS##_pop_back(TYPE_ALIAS##_ptr_t p_sdlist) {\
    if (TYPE_ALIAS##_is_empty(p_sdlist)) {\
        return ESI_SDLIST_ERR_NONE;\
    }\
    return TYPE_ALIAS##_delete(p_sdlist, TYPE_ALIAS##_peek_back(p_sdlist));\
}\
int TYPE_ALIAS##_any_if(TYPE_ALIAS##_ptr_t p_sdlist, int(*predicate)(NODE_DATA_T *)) {\
    TYPE_ALIAS##_node_ptr_t p_pivot = TYPE_ALIAS##_peek_front(p_sdlist);\
    while (p_pivot != NULL) {\
        if (predicate(&(p_pivot->node_data))) {\
            return 1;\
        }\
        if (p_pivot->next != -1) {\
            p_pivot = &(p_sdlist->node_repo[p_pivot->next]);\
        } else {\
            p_pivot = NULL;\
        }\
    }\
    return 0;\
}\
void TYPE_ALIAS##_for_each(TYPE_ALIAS##_ptr_t p_sdlist, void(*func)(NODE_DATA_T *)) {\
    TYPE_ALIAS##_node_ptr_t p_pivot = TYPE_ALIAS##_peek_front(p_sdlist);\
    while (p_pivot != NULL) {\
        func(&(p_pivot->node_data));\
        if (p_pivot->next != -1) {\
            p_pivot = &(p_sdlist->node_repo[p_pivot->next]);\
        } else {\
            p_pivot = NULL;\
        }\
    }\
}