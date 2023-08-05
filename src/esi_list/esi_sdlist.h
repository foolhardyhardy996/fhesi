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

#include "esi_err/esi_err.h"
#include "esi_functional/esi_functional.h"

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

/**
 * sdlist is a concrete class, because the resources it needs is compile-time 
 * determined.
*/
#define ESI_SDLIST_DECL(alias, elem_t, cap) \
typedef elem_t alias##_elem_t;\
extern const int alias##_cap;\
struct alias##_node {\
    int prev;\
    int next;\
    elem_t elem;\
};\
typedef struct alias##_node alias##_node_t;\
struct alias##_sdlist {\
    alias##_node_t repo[cap];\
    int len;\
    int head;\
    int tail;\
    int free_head;\
};\
typedef struct alias##_sdlist alias;\
esi_err_t alias##_init(alias *);\
int alias##_len(alias *);\
int alias##_isEmpty(alias *);\
int alias##_isFull(alias *);\
alias##_node_t *alias##_getNext(alias *, alias##_node_t *);\
alias##_node_t *alias##_getPrev(alias *, alias##_node_t *);\
alias##_node_t *alias##_peekFront(alias *);\
alias##_node_t *alias##_peekBack(alias *);\
esi_err_t alias##_insertAfter(alias *, alias##_node_t *, elem_t *);\
esi_err_t alias##_insertAfterWithAssign(alias *, alias##_node_t *, elem_t *, ESI_ASSIGN_FUNC_T(elem_t, assign));\
esi_err_t alias##_insertBefore(alias *, alias##_node_t *, elem_t *);\
esi_err_t alias##_insertBeforeWithAssign(alias *, alias##_node_t *, elem_t *, ESI_ASSIGN_FUNC_T(elem_t, assign));\
esi_err_t alias##_insertFront(alias *, elem_t *);\
esi_err_t alias##_insertFrontWithAssign(alias *, elem_t *, ESI_ASSIGN_FUNC_T(elem_t, assign));\
esi_err_t alias##_insertBack(alias *, elem_t *);\
esi_err_t alias##_insertBackWithAssign(alias *, elem_t *, ESI_ASSIGN_FUNC_T(elem_t, assign));\
esi_err_t alias##_emplaceAfter(alias *, alias##_node_t *, ESI_MODIFY_FUNC_T(elem_t, emplace));\
esi_err_t alias##_emplaceBefore(alias *, alias##_node_t *, ESI_MODIFY_FUNC_T(elem_t, emplace));\
esi_err_t alias##_emplaceFront(alias *, ESI_MODIFY_FUNC_T(elem_t, emplace));\
esi_err_t alias##_emplaceBack(alias *, ESI_MODIFY_FUNC_T(elem_t, emplace));\
esi_err_t alias##_delete(alias *, alias##_node_t *);\

#define ESI_SDLIST_IMPL(alias, elem_t, cap) \
const int alias##_cap;\
static int alias##_validateNode(alias *, alias##_node_t *);\
static int alias##_validateNode(alias *self, alias##_node_t *node) {\
    return node >= (alias##_node_t *) self->repo && node < (alias##_node_t *) self->repo + alias##_cap;\
}\
static alias##_node_t *alias##_getNodeByRepoIndex(alias *, int);\
static alias##_node_t *alias##_getNodeByRepoIndex(alias *self, int index) {\
    return &(self->repo[index]);\
}\
static int alias##_getRepoIndex(alias *, alias##_node_t *);\
static int alias##_getRepoIndex(alias *self, alias##_node_t *node) {\
    int index = node - (alias##_node_t *) self->repo;\
    if (index >= 0 && index < alias##_cap) {\
        return index;\
    } else {\
        return -1;\
    }\
}\
/** \
 * A little bit definition to make the implementation sensible: \
 * a node can be in: busy state, isolated state, free state \
*/\
static void alias##_isolateNode(alias *, alias##_node_t *);\
static void alias##_isolateNode(alias *self, alias##_node_t *node) {\
    alias##_node_t *prev, *next;\
    int index;\
    index = alias##_getRepoIndex(self, node);\
    if (index == self->head && index == self->tail) {\
        self->len = 0;\
        self->head = -1;\
        self->tail = -1;\
        return;\
    } else if (index == self->head) {\
        self->len--;\
        self->head = node->next;\
        next = alias##_getNodeByRepoIndex(self, node->next);\
        next->prev = -1;\
        node->next = -1;\
    } else if (index == self->tail) {\
        self->len--;\
        self->tail = node->prev;\
        prev = alias##_getNodeByRepoIndex(self, node->prev);\
        prev->next = -1;\
        node->prev = -1;\
    } else {\
        self->len--;\
        next = alias##_getNodeByRepoIndex(self, node->next);\
        next->prev = node->prev;\
        prev = alias##_getNodeByRepoIndex(self, node->prev);\
        prev->next = node->next;\
        node->next = -1;\
        node->prev = -1;\
    }\
}\
static alias##_node_t *alias##_allocNode(alias *);\
static alias##_node_t *alias##_allocNode(alias *self) {\
    alias##_node_t *pivot, *next;\
    if (self->free_head == -1) {\
        return NULL;\
    }\
    pivot = alias##_getNodeByRepoIndex(self, self->free_head);\
    self->free_head = pivot->next;\
    if (pivot->next != -1) {\
        next = alias##_getNodeByRepoIndex(self, pivot->next);\
        next->prev = -1;\
    }\
    return pivot;\
}\
static esi_err_t alias##_freeNode(alias *, alias##_node_t *);\
static esi_err_t alias##_freeNode(alias *self, alias##_node_t *node) {\
    int index;\
    if (node->prev != -1 || node->next != -1) {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    }\
    index = alias##_getRepoIndex(self, node);\
    node->next = self->free_head;\
    self->free_head = index;\
    return ESI_SDLIST_ERR_NONE;\
}\
const int alias##_cap = cap;\
esi_err_t alias##_init(alias *self) {\
    int i;\
    alias##_node_t *p_node;\
    self->len = 0;\
    self->head = -1;\
    self->tail = -1;\
    self->free_head = 0;\
    for (i = 0; i < alias##_cap; i++) {\
        p_node = &(self->repo[i]);\
        if (i == 0) {\
            p_node->prev = -1;\
        } else {\
            p_node->prev = i - 1;\
        }\
        if (i == (alias##_cap) - 1) {\
            p_node->next = -1;\
        } else {\
            p_node->next = i + 1;\
        }\
    }\
    return ESI_SDLIST_ERR_NONE;\
}\
int alias##_len(alias *self) {\
    return self->len;\
}\
int alias##_isEmpty(alias *self) {\
    return self->len == 0;\
}\
int alias##_isFull(alias *self) {\
    return self->free_head == -1;\
}\
alias##_node_t *alias##_getNext(alias *self, alias##_node_t *node) {\
    if (!alias##_validateNode(self, node)) {\
        return NULL;\
    }\
    if (node->next != -1) {\
        return &(self->repo[node->next]);\
    } else {\
        return NULL;\
    }\
}\
alias##_node_t *alias##_getPrev(alias *self, alias##_node_t *node) {\
    if (!alias##_validateNode(self, node)) {\
        return NULL;\
    }\
    if (node->prev != -1) {\
        return &(self->repo[node->prev]);\
    } else {\
        return NULL;\
    }\
}\
alias##_node_t *alias##_peekFront(alias *self) {\
    if (self->head == -1) {\
        return NULL;\
    } else {\
        return &(self->repo[self->head]);\
    }\
}\
alias##_node_t *alias##_peekBack(alias *self) {\
    if (self->tail == -1) {\
        return NULL;\
    } else {\
        return &(self->repo[self->tail]);\
    }\
}\
esi_err_t alias##_insertAfter(alias *self, alias##_node_t *anchor, elem_t *elem) {\
    alias##_node_t *node, *next;\
    int index;\
    node = alias##_allocNode(self);\
    if (node == NULL) {\
        return ESI_SDLIST_ERR_CAP;\
    }\
    index = alias##_getRepoIndex(self, node);\
    if (index == -1) {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    }\
    node->elem = *elem;\
    node->prev = alias##_getRepoIndex(self, anchor);\
    node->next = anchor->next;\
    if (anchor->next == -1) {\
        anchor->next = index;\
        self->tail = index;\
    } else {\
        next = alias##_getNodeByRepoIndex(self, anchor->next);\
        anchor->next = index;\
        next->prev = index;\
    }\
    self->len++;\
    return ESI_SDLIST_ERR_NONE;\
}\
esi_err_t alias##_insertAfterWithAssign(alias *self, alias##_node_t *anchor, elem_t *elem, ESI_ASSIGN_FUNC_T(elem_t, assign)) {\
    alias##_node_t *node, *next;\
    int index;\
    node = alias##_allocNode(self);\
    if (node == NULL) {\
        return ESI_SDLIST_ERR_CAP;\
    }\
    index = alias##_getRepoIndex(self, node);\
    if (index == -1) {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    }\
    assign(&(node->elem), elem);\
    node->prev = alias##_getRepoIndex(self, anchor);\
    node->next = anchor->next;\
    if (anchor->next == -1) {\
        anchor->next = index;\
        self->tail = index;\
    } else {\
        next = alias##_getNodeByRepoIndex(self, anchor->next);\
        anchor->next = index;\
        next->prev = index;\
    }\
    self->len++;\
    return ESI_SDLIST_ERR_NONE;\
}\
esi_err_t alias##_insertBefore(alias *self, alias##_node_t *anchor, elem_t *elem) {\
    alias##_node_t *node, *prev;\
    int index;\
    node = alias##_allocNode(self);\
    if (node == NULL) {\
        return ESI_SDLIST_ERR_CAP;\
    }\
    index = alias##_getRepoIndex(self, node);\
    if (index == -1) {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    }\
    node->elem = *elem;\
    node->prev = anchor->prev;\
    node->next = alias##_getRepoIndex(self, anchor);\
    if (anchor->prev == -1) {\
        anchor->prev = index;\
        self->head = index;\
    } else {\
        prev = alias##_getNodeByRepoIndex(self, anchor->prev);\
        anchor->prev = index;\
        prev->next = index;\
    }\
    self->len++;\
    return ESI_SDLIST_ERR_NONE;\
}\
esi_err_t alias##_insertBeforeWithAssign(alias *self, alias##_node_t *anchor, elem_t *elem, ESI_ASSIGN_FUNC_T(elem_t, assign)) {\
    alias##_node_t *node, *prev;\
    int index;\
    node = alias##_allocNode(self);\
    if (node == NULL) {\
        return ESI_SDLIST_ERR_CAP;\
    }\
    index = alias##_getRepoIndex(self, node);\
    if (index == -1) {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    }\
    assign(&(node->elem), elem);\
    node->prev = anchor->prev;\
    node->next = alias##_getRepoIndex(self, anchor);\
    if (anchor->prev == -1) {\
        anchor->prev = index;\
        self->head = index;\
    } else {\
        prev = alias##_getNodeByRepoIndex(self, anchor->prev);\
        anchor->prev = index;\
        prev->next = index;\
    }\
    self->len++;\
    return ESI_SDLIST_ERR_NONE;\
}\
esi_err_t alias##_insertFront(alias *self, elem_t *elem) {\
    alias##_node_t *node, *head;\
    int index;\
    if (self->head == -1) {\
        node = alias##_allocNode(self);\
        if (node == NULL) {\
            return ESI_SDLIST_ERR_CAP;\
        }\
        node->prev = -1;\
        node->next =-1;\
        node->elem = *elem;\
        index = alias##_getRepoIndex(self, node);\
        self->head = index;\
        self->tail = index;\
        self->len++;\
        return ESI_SDLIST_ERR_NONE;\
    } else {\
        head = alias##_getNodeByRepoIndex(self, self->head);\
        return alias##_insertBefore(self, head, elem);\
    }\
}\
esi_err_t alias##_insertFrontWithAssign(alias *self, elem_t *elem, ESI_ASSIGN_FUNC_T(elem_t, assign)) {\
    alias##_node_t *node, *head;\
    int index;\
    if (self->head == -1) {\
        node = alias##_allocNode(self);\
        if (node == NULL) {\
            return ESI_SDLIST_ERR_CAP;\
        }\
        node->prev = -1;\
        node->next =-1;\
        assign(&(node->elem), elem);\
        index = alias##_getRepoIndex(self, node);\
        self->head = index;\
        self->tail = index;\
        self->len++;\
        return ESI_SDLIST_ERR_NONE;\
    } else {\
        head = alias##_getNodeByRepoIndex(self, self->head);\
        return alias##_insertBeforeWithAssign(self, head, elem, assign);\
    }\
}\
esi_err_t alias##_insertBack(alias *self, elem_t *elem) {\
    alias##_node_t *node, *tail;\
    int index;\
    if (self->tail == -1) {\
        node = alias##_allocNode(self);\
        if (node == NULL) {\
            return ESI_SDLIST_ERR_CAP;\
        }\
        node->prev = -1;\
        node->next =-1;\
        node->elem = *elem;\
        index = alias##_getRepoIndex(self, node);\
        self->head = index;\
        self->tail = index;\
        self->len++;\
        return ESI_SDLIST_ERR_NONE;\
    } else {\
        tail = alias##_getNodeByRepoIndex(self, self->tail);\
        return alias##_insertAfter(self, tail, elem);\
    }\
}\
esi_err_t alias##_insertBackWithAssign(alias *self, elem_t *elem, ESI_ASSIGN_FUNC_T(elem_t, assign)) {\
    alias##_node_t *node, *tail;\
    int index;\
    if (self->tail == -1) {\
        node = alias##_allocNode(self);\
        if (node == NULL) {\
            return ESI_SDLIST_ERR_CAP;\
        }\
        node->prev = -1;\
        node->next =-1;\
        assign(&(node->elem), elem);\
        index = alias##_getRepoIndex(self, node);\
        self->head = index;\
        self->tail = index;\
        self->len++;\
        return ESI_SDLIST_ERR_NONE;\
    } else {\
        tail = alias##_getNodeByRepoIndex(self, self->tail);\
        return alias##_insertAfterWithAssign(self, tail, elem, assign);\
    }\
}\
esi_err_t alias##_emplaceAfter(alias *self, alias##_node_t *anchor, ESI_MODIFY_FUNC_T(elem_t, emplace)) {\
    alias##_node_t *node, *next;\
    int index;\
    node = alias##_allocNode(self);\
    if (node == NULL) {\
        return ESI_SDLIST_ERR_CAP;\
    }\
    index = alias##_getRepoIndex(self, node);\
    if (index == -1) {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    }\
    emplace(&(node->elem));\
    node->prev = alias##_getRepoIndex(self, anchor);\
    node->next = anchor->next;\
    if (anchor->next == -1) {\
        anchor->next = index;\
        self->tail = index;\
    } else {\
        next = alias##_getNodeByRepoIndex(self, anchor->next);\
        anchor->next = index;\
        next->prev = index;\
    }\
    self->len++;\
    return ESI_SDLIST_ERR_NONE;\
}\
esi_err_t alias##_emplaceBefore(alias *self, alias##_node_t *anchor, ESI_MODIFY_FUNC_T(elem_t, emplace)) {\
    alias##_node_t *node, *prev;\
    int index;\
    node = alias##_allocNode(self);\
    if (node == NULL) {\
        return ESI_SDLIST_ERR_CAP;\
    }\
    index = alias##_getRepoIndex(self, node);\
    if (index == -1) {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    }\
    emplace(&(node->elem));\
    node->prev = anchor->prev;\
    node->next = alias##_getRepoIndex(self, anchor);\
    if (anchor->prev == -1) {\
        anchor->prev = index;\
        self->head = index;\
    } else {\
        prev = alias##_getNodeByRepoIndex(self, anchor->prev);\
        anchor->prev = index;\
        prev->next = index;\
    }\
    self->len++;\
    return ESI_SDLIST_ERR_NONE;\
}\
esi_err_t alias##_emplaceFront(alias *self, ESI_MODIFY_FUNC_T(elem_t, emplace)) {\
    alias##_node_t *node, *head;\
    int index;\
    if (self->head == -1) {\
        node = alias##_allocNode(self);\
        if (node == NULL) {\
            return ESI_SDLIST_ERR_CAP;\
        }\
        node->prev = -1;\
        node->next = -1;\
        emplace(&(node->elem));\
        index = alias##_getRepoIndex(self, node);\
        self->head = index;\
        self->tail = index;\
        self->len++;\
        return ESI_SDLIST_ERR_NONE;\
    } else {\
        head = alias##_getNodeByRepoIndex(self, self->head);\
        return alias##_emplaceBefore(self, head, emplace);\
    }\
}\
esi_err_t alias##_emplaceBack(alias *self, ESI_MODIFY_FUNC_T(elem_t, emplace)) {\
    alias##_node_t *node, *tail;\
    int index;\
    if (self->tail == -1) {\
        node = alias##_allocNode(self);\
        if (node == NULL) {\
            return ESI_SDLIST_ERR_CAP;\
        }\
        node->prev = -1;\
        node->next =-1;\
        emplace(&(node->elem));\
        index = alias##_getRepoIndex(self, node);\
        self->head = index;\
        self->tail = index;\
        self->len++;\
        return ESI_SDLIST_ERR_NONE;\
    } else {\
        tail = alias##_getNodeByRepoIndex(self, self->tail);\
        return alias##_emplaceAfter(self, tail, emplace);\
    }\
}\
esi_err_t alias##_delete(alias *self, alias##_node_t *node) {\
    if (!alias##_validateNode(self, node)) {\
        return ESI_SDLIST_ERR_INVALID_NODE;\
    }\
    alias##_isolateNode(self, node);\
    alias##_freeNode(self, node);\
    return ESI_SDLIST_ERR_NONE;\
}\

