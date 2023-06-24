#pragma once 

/**
 * @file esi_fsm.h
 * @brief "esi_fsm.h" provides templates to facilitate the implementation 
 * of simple finite state machine.
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.06.15
 * 
*/

#include "esi_arr/esi_arr.h"

/**
 * Related types of finite state machine:
 * 1. fsm_state = state_id + state_memory
 * 2. fsm_event = event_id + event_arg
 * 3. fsm_trans_func = (current_state, event) -> next_state
 * 4. fsm_trans = fsm_trans_func + (state_id, event_id)
*/

enum esi_fsm_err {
    ESI_FSM_ERR_NONE = 0,
    ESI_FSM_ERR_STATE_EXIST = 1,
    ESI_FSM_ERR_EVENT_EXIST = 2,
    ESI_FSM_ERR_TRANS_EXIST = 3,
    ESI_FSM_ERR_CAP = 4,
    ESI_FSM_ERR_TRANS = 5
};

#define ESI_FSM_ERR_MSG {\
    "esi_fsm: ok", /*0*/\
    "esi_fsm: state_id already exists", /*1*/\
    "esi_fsm: event_id already exists", /*2*/\
    "esi_fsm: transition for (state_id, event_id) exists", /*3*/\
    "esi_fsm: capacity has been reached", /*4*/\
    "esi_fsm: error occured at transition" /*5*/\
}

const char *esi_arr_strerror(int err);

#define ESI_FSM_TYPE_DECL(TYPE_ALIAS, STATE_MEM_T, EVENT_ARG_T, STATE_LIST_CAP, EVENT_LIST_CAP, TRANS_LIST_CAP) \
struct esi_fsm_state_##STATE_MEM_T {\
    int state_id;\
    STATE_MEM_T state_mem;\
};\
typedef struct esi_fsm_state_##STATE_MEM_T esi_fsm_state_##STATE_MEM_T##_st;\
typedef struct esi_fsm_state_##STATE_MEM_T TYPE_ALIAS##_state_t;\
typedef esi_fsm_state_##STATE_MEM_T##_st * esi_fsm_state_##STATE_MEM_T##_st_ptr_t;\
typedef esi_fsm_state_##STATE_MEM_T##_st * TYPE_ALIAS##_state_ptr_t;\
struct esi_fsm_event_##EVENT_ARG_T {\
    int event_id;\
    EVENT_ARG_T event_arg;\
};\
typedef struct esi_fsm_event_##EVENT_ARG_T esi_fsm_event_##EVENT_ARG_T##_st;\
typedef struct esi_fsm_event_##EVENT_ARG_T TYPE_ALIAS##_event_t;\
typedef esi_fsm_event_##EVENT_ARG_T##_st * esi_fsm_event_##EVENT_ARG_T##_st_ptr_t;\
typedef esi_fsm_event_##EVENT_ARG_T##_st * TYPE_ALIAS##_event_ptr_t;\
typedef int (*esi_fsm_##STATE_MEM_T##_##EVENT_ARG_T##_trans_func_t)(TYPE_ALIAS##_state_ptr_t, TYPE_ALIAS##_event_ptr_t, TYPE_ALIAS##_state_ptr_t);\
typedef esi_fsm_##STATE_MEM_T##_##EVENT_ARG_T##_trans_func_t TYPE_ALIAS##_trans_func_t;\
struct esi_fsm_trans_##STATE_MEM_T##_##EVENT_ARG_T {\
    int state_id;\
    int event_id;\
    TYPE_ALIAS##_trans_func_t trans_func;\
};\
typedef struct esi_fsm_trans_##STATE_MEM_T##_##EVENT_ARG_T \
esi_fsm_trans_##STATE_MEM_T##_##EVENT_ARG_T##_st;\
typedef struct esi_fsm_trans_##STATE_MEM_T##_##EVENT_ARG_T \
TYPE_ALIAS##_trans_t;\
typedef esi_fsm_trans_##STATE_MEM_T##_##EVENT_ARG_T##_st * \
esi_fsm_trans_##STATE_MEM_T##_##EVENT_ARG_T##_st_ptr_t;\
typedef esi_fsm_trans_##STATE_MEM_T##_##EVENT_ARG_T##_st * \
TYPE_ALIAS##_trans_ptr_t;\
/* supporting array types */ \
ESI_ARR_TYPE_DECL(TYPE_ALIAS##_id_arr_t, int, 32);\
ESI_ARR_TYPE_DECL(TYPE_ALIAS##_trans_arr_t, TYPE_ALIAS##_trans_t, 32);\
/* the fsm type */ \
struct esi_fsm_##STATE_MEM_T##_##EVENT_ARG_T##_##STATE_LIST_CAP##_##EVENT_LIST_CAP##_##TRANS_LIST_CAP {\
    TYPE_ALIAS##_id_arr_t state_id_list;\
    TYPE_ALIAS##_id_arr_t event_id_list;\
    TYPE_ALIAS##_trans_arr_t trans_list;\
    TYPE_ALIAS##_trans_t default_trans;\
    TYPE_ALIAS##_state_t current_state;\
};\
typedef struct esi_fsm_##STATE_MEM_T##_##EVENT_ARG_T##_##STATE_LIST_CAP##_##EVENT_LIST_CAP##_##TRANS_LIST_CAP \
esi_fsm_##STATE_MEM_T##_##EVENT_ARG_T##_##STATE_LIST_CAP##_##EVENT_LIST_CAP##_##TRANS_LIST_CAP##_st;\
typedef esi_fsm_##STATE_MEM_T##_##EVENT_ARG_T##_##STATE_LIST_CAP##_##EVENT_LIST_CAP##_##TRANS_LIST_CAP##_st TYPE_ALIAS;\
typedef esi_fsm_##STATE_MEM_T##_##EVENT_ARG_T##_##STATE_LIST_CAP##_##EVENT_LIST_CAP##_##TRANS_LIST_CAP##_st * \
esi_fsm_##STATE_MEM_T##_##EVENT_ARG_T##_##STATE_LIST_CAP##_##EVENT_LIST_CAP##_##TRANS_LIST_CAP##_st_ptr_t;\
typedef esi_fsm_##STATE_MEM_T##_##EVENT_ARG_T##_##STATE_LIST_CAP##_##EVENT_LIST_CAP##_##TRANS_LIST_CAP##_st * \
TYPE_ALIAS##_ptr_t;\
/* methods for fsm */\
int TYPE_ALIAS##_set_current_state(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_state_ptr_t);\
int TYPE_ALIAS##_add_state(TYPE_ALIAS##_ptr_t, int /* state_id */);\
int TYPE_ALIAS##_add_event(TYPE_ALIAS##_ptr_t, int /* state_id */, int /* event_id */, TYPE_ALIAS##_trans_func_t);\
int TYPE_ALIAS##_set_default_trans(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_trans_func_t);\
int TYPE_ALIAS##_trans(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_event_ptr_t);

#define ESI_FSM_STATE_T(FSM_T) FSM_T##_state_t
#define ESI_FSM_EVENT_T(FSM_T) FSM_T##_event_t
#define ESI_FSM_TRANS_FUNC_T(FSM_T) FSM_T##_trans_func_t
#define ESI_FSM_TRANS_T(FSM_T) FSM_T##_trans_t

#define ESI_FSM_DECL(FSM_T, VAR) FSM_T VAR = {\
    .state_id_list = ESI_ARR_INITIALIZER(TYPE_ALIAS##_id_arr_t),\
    .event_id_list = ESI_ARR_INITIALIZER(TYPE_ALIAS##_id_arr_t),\
    .trans_list = ESI_ARR_INITIALIZER(TYPE_ALIAS##_trans_arr_t),\
    .default_trans = {.state_id = -1, .event_id = -1, .trans_func = FSM_T##_null_trans_func}\
}
#define ESI_FSM_SET_CURRENT_STATE(FSM_T, p_fsm, p_state) FSM_T##_set_current_state(p_fsm, p_state)

#define ESI_FSM_TYPE_IMPL(TYPE_ALIAS, STATE_MEM_T, EVENT_ARG_T, STATE_LIST_CAP, EVENT_LIST_CAP, TRANS_LIST_CAP) \
/* supporting array types */ \
ESI_ARR_TYPE_IMPL(TYPE_ALIAS##_id_arr_t, int, 32);\
static int TYPE_ALIAS##_trans_eq(TYPE_ALIAS##_trans_ptr_t, TYPE_ALIAS##_trans_ptr_t);\
static int TYPE_ALIAS##_trans_eq(TYPE_ALIAS##_trans_ptr_t trans1, TYPE_ALIAS##_trans_ptr_t trans2) {\
    return (trans1->state_id == trans2->state_id) && (trans1->event_id == trans2->event_id) && (trans1->trans_func == trans2->trans_func);\
}\
ESI_ARR_TYPE_IMPL_WITH_EQ(TYPE_ALIAS##_trans_arr_t, TYPE_ALIAS##_trans_t, 32, TYPE_ALIAS##_trans_eq);\
int TYPE_ALIAS##_set_current_state(TYPE_ALIAS##_ptr_t p_fsm, TYPE_ALIAS##_state_ptr_t p_state) {\
    p_fsm->current_state = *p_state;\
    return ESI_FSM_ERR_NONE;\
}\
int TYPE_ALIAS##_add_state(TYPE_ALIAS##_ptr_t p_fsm, int state_id) {\
    /** \
     * algorithm: \
     * 1. check if state_id is already in list \
     * 2. add state_id into list if not full \
     */ \
    if (ESI_ARR_CONTAINS(TYPE_ALIAS##_id_arr_t, &(p_fsm->state_id_list), state_id)) {\
        return ESI_FSM_ERR_STATE_EXIST;\
    }\
    if (ESI_ARR_IS_FULL(TYPE_ALIAS##_id_arr_t, &(p_fsm->state_id_list))) {\
        return ESI_FSM_ERR_CAP;\
    }\
    ESI_ARR_APPEND(TYPE_ALIAS##_id_arr_t, &(p_fsm->state_id_list), state_id);\
    return ESI_FSM_ERR_NONE;\
}\
static int TYPE_ALIAS##_predicate_id_match(TYPE_ALIAS##_trans_t);\
static int TYPE_ALIAS##_predicate_id_match_state_id;\
static int TYPE_ALIAS##_predicate_id_match_event_id;\
static int TYPE_ALIAS##_predicate_id_match(TYPE_ALIAS##_trans_t trans) {\
    if (trans.state_id == TYPE_ALIAS##_predicate_id_match_state_id && trans.event_id == TYPE_ALIAS##_predicate_id_match_event_id) {\
        return 1;\
    } else {\
        return 0;\
    }\
}\
int TYPE_ALIAS##_add_event(TYPE_ALIAS##_ptr_t p_fsm, int state_id, int event_id, TYPE_ALIAS##_trans_func_t func) {\
    TYPE_ALIAS##_trans_t trans;\
    TYPE_ALIAS##_predicate_id_match_state_id = state_id;\
    TYPE_ALIAS##_predicate_id_match_event_id = event_id;\
    if (ESI_ARR_ANY(TYPE_ALIAS##_trans_arr_t, &(p_fsm->trans_list), TYPE_ALIAS##_predicate_id_match)) {\
        return ESI_FSM_ERR_TRANS_EXIST;\
    }\
    if (ESI_ARR_IS_FULL(TYPE_ALIAS##_trans_arr_t, &(p_fsm->trans_list))) {\
        return ESI_FSM_ERR_CAP;\
    }\
    trans.state_id = state_id;\
    trans.event_id = event_id;\
    trans.trans_func = func;\
    ESI_ARR_APPEND(TYPE_ALIAS##_trans_arr_t, &(p_fsm->trans_list), trans);\
    return ESI_FSM_ERR_NONE;\
}\
static int TYPE_ALIAS##_null_trans_func(TYPE_ALIAS##_state_ptr_t, TYPE_ALIAS##_event_ptr_t, TYPE_ALIAS##_state_ptr_t);\
static int TYPE_ALIAS##_null_trans_func(TYPE_ALIAS##_state_ptr_t current_state, TYPE_ALIAS##_event_ptr_t event, TYPE_ALIAS##_state_ptr_t next_state) {\
    return ESI_FSM_ERR_NONE;\
}\
int TYPE_ALIAS##_set_default_trans(TYPE_ALIAS##_ptr_t p_fsm, TYPE_ALIAS##_trans_func_t func) {\
    p_fsm->default_trans.trans_func = func;\
    return ESI_FSM_ERR_NONE;\
}\
int TYPE_ALIAS##_trans(TYPE_ALIAS##_ptr_t p_fsm, TYPE_ALIAS##_event_ptr_t p_event) {\
    /**\
     * 1. find if there are transition registered for (state_id, event_id)\
     * 2. if not call default transition\
    */\
    int state_id = p_fsm->current_state.state_id;\
    int event_id = p_event->event_id;\
    int trans_id;\
    int ret;\
    TYPE_ALIAS##_predicate_id_match_state_id = state_id;\
    TYPE_ALIAS##_predicate_id_match_event_id = event_id;\
    trans_id = ESI_ARR_FIND_IF(TYPE_ALIAS##_trans_arr_t, &(p_fsm->trans_list), TYPE_ALIAS##_predicate_id_match);\
    if (trans_id == -1) {\
        ret = p_fsm->default_trans.trans_func(&(p_fsm->current_state), p_event, &(p_fsm->current_state));\
    } else {\
        ret = p_fsm->trans_list.data[trans_id].trans_func(&(p_fsm->current_state), p_event, &(p_fsm->current_state));\
    }\
    if (ret != 0) {\
        return ESI_FSM_ERR_TRANS;\
    }\
    return ESI_FSM_ERR_NONE;\
}\
