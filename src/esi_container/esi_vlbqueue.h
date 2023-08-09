#pragma once 

/**
 * @file esi_vlbqueue.h
 * @brief varlen_bytes_deque provide a queue operation interfaces and as a 
 * container for variable-length byte strings.
 * 
 * @author Li Weida
 * @date 2023.08.08
*/

#include "esi_err/esi_err.h"
#include "esi_list/esi_sdlist.h"
#include "esi_str/esi_str.h"

enum esi_vlbqueue_err {
    ESI_VLBQUEUE_ERR_NONE = 0,
    ESI_VLBQUEUE_ERR_CAP = 1,
    ESI_VLBQUEUE_ERR_EMPTY = 2, 
    ESI_VLBQUEUE_ERR_BUF = 3,
    ESI_VLBQUEUE_ERR_INVALID = 4
};

#define ESI_VLBQUEUE_ERR_MSG {\
    "esi_vlbqueue: ok", /*0*/\
    "esi_vlbqueue: capacity has been reached", /*1*/\
    "esi_vlbqueue: empty", /*2*/\
    "esi_vlbqueue: remainder buffer is not sufficient", /*3*/\
    "esi_vlbqueue: invalid argument" /*4*/\
}

const char *esi_vlbqueue_strerror(int err);

#define ESI_VARLEN_BYTES_QUEUE_DECL(alias, cap, bufsz) \
extern const int alias##_cap;\
extern const int alias##_bufsz;\
struct alias##_cb {\
    int start;\
    int end;\
};\
typedef struct alias##_cb alias##_cb_t;\
ESI_SDLIST_DECL(alias##_cbrepo_t, alias##_cb_t, cap)\
struct alias##_queue {\
    char buf[bufsz];\
    /*invariant: boundary is larger than index; (index, boundary) never */\
    /*intersect with any control block*/\
    int index;\
    int boundary;\
    alias##_cbrepo_t cbrepo;\
    alias##_cbrepo_t_node_t *corner_node;\
};\
typedef struct alias##_queue alias;\
esi_err_t alias##_init(alias *);\
esi_err_t alias##_len(alias *);\
esi_err_t alias##_insertBack(alias *, char *, int);\
esi_err_t alias##_peekFront(alias *, char **, int *);\
esi_err_t alias##_deleteFront(alias *);

#define ESI_VARLEN_BYTES_QUEUE_IMPL(alias, cap, bufsz) \
const int alias##_cap = cap;\
const int alias##_bufsz = bufsz;\
ESI_SDLIST_IMPL(alias##_cbrepo_t, alias##_cb_t, cap)\
static int alias##_shouldTurnAround(alias *, int);\
static int alias##_shouldTurnAround(alias *self, int len) {\
    alias##_cb_t headcb;\
    alias##_cbrepo_t_node_t *head_node;\
    if (len <= (self->boundary - self->index)) {\
        return 0;\
    }\
    if (self->corner_node != NULL) {\
        return 0;\
    }\
    head_node = alias##_cbrepo_t_peekFront(&(self->cbrepo));\
    if (head_node == NULL) {\
        return 0;\
    }\
    headcb = head_node->elem;\
    if (headcb.start <= len) {\
        return 0;\
    } else {\
        return 1;\
    }\
}\
static void alias##_turnAround(alias *);\
static void alias##_turnAround(alias *self) {\
    self->corner_node = alias##_cbrepo_t_peekBack(&(self->cbrepo));\
    self->index = 0;\
    self->boundary = alias##_cbrepo_t_peekFront(&(self->cbrepo))->elem.start;\
}\
esi_err_t alias##_init(alias *self) {\
    self->index = 0;\
    self->boundary = bufsz;\
    alias##_cbrepo_t_init(&(self->cbrepo));\
    self->corner_node = NULL;\
    return ESI_VLBQUEUE_ERR_NONE;\
}\
esi_err_t alias##_len(alias *self) {\
    return alias##_cbrepo_t_len(&(self->cbrepo));\
}\
esi_err_t alias##_insertBack(alias *self, char *s, int len) {\
    alias##_cb_t cb;\
    if (alias##_shouldTurnAround(self, len)) {\
        alias##_turnAround(self);\
    }\
    if (len > (self->boundary - self->index)) {\
        return ESI_VLBQUEUE_ERR_BUF;\
    }\
    cb.start = self->index;\
    cb.end = self->index + len;\
    memcpy(self->buf + cb.start, s, len);\
    alias##_cbrepo_t_insertBack(&(self->cbrepo), &cb);\
    self->index = cb.end;\
    return ESI_VLBQUEUE_ERR_NONE;\
}\
esi_err_t alias##_peekFront(alias *self, char **s, int *len) {\
    alias##_cb_t headcb;\
    alias##_cbrepo_t_node_t *head_node;\
    if (s == NULL || len == NULL) {\
        return ESI_VLBQUEUE_ERR_INVALID;\
    }\
    head_node = alias##_cbrepo_t_peekFront(&(self->cbrepo));\
    if (head_node == NULL) {\
        return ESI_VLBQUEUE_ERR_EMPTY;\
    }\
    headcb = head_node->elem;\
    *s = self->buf + headcb.start;\
    *len = headcb.end - headcb.start;\
    return ESI_VLBQUEUE_ERR_NONE;\
}\
esi_err_t alias##_deleteFront(alias *self) {\
    alias##_cb_t headcb;\
    alias##_cbrepo_t_node_t *head_node;\
    head_node = alias##_cbrepo_t_peekFront(&(self->cbrepo));\
    if (head_node == NULL) {\
        return ESI_VLBQUEUE_ERR_EMPTY;\
    }\
    headcb = head_node->elem;\
    if (head_node == self->corner_node) {\
        self->corner_node = NULL;\
        self->boundary = bufsz;\
    } else if (self->corner_node != NULL) {\
        self->boundary = headcb.end;\
    }\
    alias##_cbrepo_t_delete(&(self->cbrepo), head_node);\
    return ESI_VLBQUEUE_ERR_NONE;\
}
