#pragma once 

/**
 * @file esi_fsm.h
 * @brief "esi_fsm.h" provides common interfaces for finite state machine.
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.06.13
 * 
*/

/**
 * Finite state machine is defined by state table, event table, and transition list. 
*/

typedef int esi_fsm_state_id_t;
struct esi_fsm_state {
    esi_fsm_state_id_t state_id;
    void *state_memory;
};

typedef int esi_fsm_event_id_t;
struct esi_fsm_event {
    esi_fsm_event_id_t event_id;
    void *event_arg;
};

/**
 * although a transition list is required in the formal definition of FSM, 
 * I think this idea can be implemented as one function rather than a list of 
 * functions.
*/
typedef int (*esi_fsm_trans_func_t)(
    void * /*pointer fsm*/,
    struct esi_fsm_state /*current state*/, 
    struct esi_fsm_event /*current event*/,
    struct esi_fsm_state */*next state*/);

struct esi_fsm_trans {
    esi_fsm_state_id_t state_id;
    esi_fsm_event_id_t event_id;
    esi_fsm_trans_func_t trans;
};

struct esi_fsm {
    esi_fsm_state_id_t *state_list;
    esi_fsm_event_id_t *event_list;
    esi_fsm_trans_func_t trans;
    struct esi_fsm_state current_state;
};

/**
 * For now the interfaces are complete for define a FSM, but it's not useful 
 * to facilitate the composition of a FSM.
*/

/**
 * First utility for composing FSM:
 * 1. provide a list of state id
 * 2. provide a list of event id
 * 3. provide a list of defined transition
 * 4. provide a default action for undefined transition
*/
struct esi_fsm_from_lists {
    esi_fsm_state_id_t *state_list;
    int state_list_len;
    esi_fsm_event_id_t *event_list;
    int event_list_len;
    struct esi_fsm_trans *trans_list;
    int trans_list_len;
    esi_fsm_trans_func_t null_trans;
    esi_fsm_trans_func_t trans;
    struct esi_fsm_state current_state;
};
/**
 * 
 * @note the ownship of list is not transferred to fsm, it is the caller's 
 * responsibility to ensure the lists are accessible during the lifetime of
 * the fsm.
*/
int esi_fsm_create_from_lists(
    struct esi_fsm_from_lists *fsm,
    esi_fsm_state_id_t *state_list,
    int state_list_len,
    esi_fsm_event_id_t *event_list,
    int event_list_len,
    struct esi_fsm_trans *trans_list,
    int trans_list_len,
    esi_fsm_trans_func_t null_trans,
    struct esi_fsm_state initial_state);

int esi_fsm_from_lists_trans(
    void * fsm,
    struct esi_fsm_state, 
    struct esi_fsm_event, 
    struct esi_fsm_state *);