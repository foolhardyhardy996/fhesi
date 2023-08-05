#pragma once 

/**
 * @file esi_rrserver.h
 * @brief request-response is such a template class, that when proper 
 * request type and response type is provided, it provides functionality 
 * to map incomming request to associated handler and return response.
 * 
 * @author Li Weida
 * @date 2023.07.29
*/

#include "esi_err/esi_err.h"

enum esi_rrserver_err {
    ESI_RRSERVER_ERR_NONE = 0,
    ESI_RRSERVER_ERR_NO_HANDLER = 1,
    ESI_RRSERVER_ERR_INVALID_ID = 2,
    ESI_RRSERVER_ERR_FULL = 3,
    ESI_RRSERVER_ERR_HANDLER = 4
};

#define ESI_RRSERVER_ERR_MSG {\
    "esi_rrserver: ok", /*0*/\
    "esi_rrserver: no matching handler", /*1*/\
    "esi_rrserver: invalid handler id", /*2*/\
    "esi_rrserver: handler registry is full", /*3*/\
    "esi_rrserver: handler report error" /*4*/\
}

const char *esi_rrserver_strerror(int err);

/**
 * 
 * TODO:
 * 1. use iterator if possible
 * 2. use static linked list to replace the plain array
*/

#define ESI_ARRAY_BASED_RRSERVER_DECL(type_alias, req_t, res_t, hdr_cap) \
typedef req_t type_alias##_req_t;\
typedef res_t type_alias##_res_t;\
extern const int type_alias##_hdr_cap;\
typedef esi_err_t (*type_alias##_hdr_func_t)(req_t *, res_t *);\
typedef int (*type_alias##_hdr_mapper_t)(req_t *);\
typedef int (*type_alias##_hdr_picker_t)(req_t *);\
struct type_alias##_hdr_ctl_blk {\
    type_alias##_hdr_func_t hdr_func;\
    type_alias##_hdr_picker_t hdr_picker;\
    int free_flag;\
};\
typedef struct type_alias##_hdr_ctl_blk type_alias##_hdr_ctl_blk_t;\
struct type_alias##_array_based_rrserver {\
    type_alias##_hdr_mapper_t mapper;\
    type_alias##_hdr_ctl_blk_t cbs[hdr_cap];\
};\
typedef struct type_alias##_array_based_rrserver type_alias;\
esi_err_t type_alias##_init(type_alias *);\
esi_err_t type_alias##_setFallbackHandler(type_alias *, type_alias##_hdr_func_t, type_alias##_hdr_func_t *);\
esi_err_t type_alias##_setMapper(type_alias *, type_alias##_hdr_mapper_t, type_alias##_hdr_mapper_t *);\
esi_err_t type_alias##_setPicker(type_alias *, int, type_alias##_hdr_picker_t, type_alias##_hdr_picker_t *);\
esi_err_t type_alias##_register(type_alias *, type_alias##_hdr_func_t, int *);\
esi_err_t type_alias##_serve(type_alias *, req_t *, res_t *);\

#define ESI_ARRAY_BASED_RRSERVER_IMPL(type_alias, req_t, res_t, hdr_cap) \
const int type_alias##_hdr_cap = hdr_cap;\
static const int type_alias##_fallback_hdr_id = 0;\
static esi_err_t type_alias##_default_fallback_hdr(req_t *, res_t *);\
static esi_err_t type_alias##_default_fallback_hdr(req_t *req, res_t *res) {\
    return ESI_RRSERVER_ERR_NO_HANDLER;\
}\
static int type_alias##_default_mapper(req_t *);\
static int type_alias##_default_mapper(req_t *req) {\
    return type_alias##_fallback_hdr_id;\
}\
static int type_alias##_default_picker(req_t *);\
static int type_alias##_default_picker(req_t *req) {\
    return 0;\
}\
static int type_alias##_validate_hdr_id(type_alias *, int);\
static int type_alias##_validate_hdr_id(type_alias *self, int id) {\
    return id > 0 && id < hdr_cap && self->cbs[id].free_flag == 0;\
}\
static int type_alias##_find_free_cb_index(type_alias *);\
static int type_alias##_find_free_cb_index(type_alias *self) {\
    int i = 1;\
    for (; i < type_alias##_hdr_cap; i++) {\
        if (self->cbs[i].free_flag) {\
            return i;\
        }\
    }\
    return -1;\
}\
static void type_alias##_takeup_cb(type_alias *, int, type_alias##_hdr_func_t, type_alias##_hdr_picker_t);\
static void type_alias##_takeup_cb(type_alias *self, int hdr_id, type_alias##_hdr_func_t hdr, type_alias##_hdr_picker_t picker) {\
    self->cbs[hdr_id].hdr_func = hdr;\
    self->cbs[hdr_id].hdr_picker = picker;\
    self->cbs[hdr_id].free_flag = 0;\
}\
esi_err_t type_alias##_init(type_alias *self) {\
    int i = 1;\
    self->mapper = type_alias##_default_mapper;\
    type_alias##_takeup_cb(self, type_alias##_fallback_hdr_id, type_alias##_default_fallback_hdr, type_alias##_default_picker);\
    for (; i < type_alias##_hdr_cap; i++) {\
        self->cbs[i].free_flag = 1;\
    }\
    return ESI_RRSERVER_ERR_NONE;\
}\
esi_err_t type_alias##_setFallbackHandler(type_alias *self, type_alias##_hdr_func_t new_hdr, type_alias##_hdr_func_t *p_old_hdr) {\
    if (p_old_hdr != NULL) {\
        *p_old_hdr = self->cbs[type_alias##_fallback_hdr_id].hdr_func;\
    }\
    self->cbs[type_alias##_fallback_hdr_id].hdr_func = new_hdr;\
    return ESI_RRSERVER_ERR_NONE;\
}\
esi_err_t type_alias##_setMapper(type_alias *self, type_alias##_hdr_mapper_t new_mapper, type_alias##_hdr_mapper_t *p_old_mapper) {\
    if (p_old_mapper != NULL) {\
        *p_old_mapper = self->mapper;\
    }\
    self->mapper = new_mapper;\
    return ESI_RRSERVER_ERR_NONE;\
}\
esi_err_t type_alias##_setPicker(type_alias *self, int hdr_id, type_alias##_hdr_picker_t new_picker, type_alias##_hdr_picker_t *p_old_picker) {\
    if (!type_alias##_validate_hdr_id(self, hdr_id)) {\
        return ESI_RRSERVER_ERR_INVALID_ID;\
    }\
    if (p_old_picker != NULL) {\
        *p_old_picker = self->cbs[hdr_id].hdr_picker;\
    }\
    self->cbs[hdr_id].hdr_picker = new_picker;\
    return ESI_RRSERVER_ERR_NONE;\
}\
esi_err_t type_alias##_register(type_alias *self, type_alias##_hdr_func_t hdr, int *p_hdr_id) {\
    int free_index = type_alias##_find_free_cb_index(self);\
    if (free_index == -1) {\
        return ESI_RRSERVER_ERR_FULL;\
    }\
    type_alias##_takeup_cb(self, free_index, hdr, type_alias##_default_picker);\
    *p_hdr_id = free_index;\
    return ESI_RRSERVER_ERR_NONE;\
}\
esi_err_t type_alias##_serve(type_alias *self, req_t *req, res_t *res) {\
    int hdr_id;\
    int ret;\
    hdr_id = self->mapper(req);\
    if (!type_alias##_validate_hdr_id(self, hdr_id)) {\
        int i = 1;\
        hdr_id = type_alias##_fallback_hdr_id;\
        for (; i < type_alias##_hdr_cap; i++) {\
            if (!self->cbs[i].free_flag && self->cbs[i].hdr_picker(req)) {\
                hdr_id = i;\
                break;\
            }\
        }\
    }\
    ret = self->cbs[hdr_id].hdr_func(req, res);\
    if (ret != 0) {\
        return ESI_RRSERVER_ERR_HANDLER;\
    }\
    return ESI_RRSERVER_ERR_NONE;\
}

