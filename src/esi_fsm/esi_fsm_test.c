#include "esi_fsm.h"
#include <stdio.h>

#define INITIAL_STATE (0)
#define FACTORY_STATE (1)
#define READY_STATE (2)
#define WORKING_STATE (3)
#define STATE_LIST_LEN (4)

#define MANU (0)
#define AUTH (1)
#define WITHDRAW (2)
#define START (3)
#define STOP (4)
#define WORK (5)
#define EVENT_LIST_LEN (6)

#define TRANS_LIST_LEN (7)

ESI_FSM_TYPE_DECL(dev_fsm_t, int, int, STATE_LIST_LEN, EVENT_LIST_LEN, TRANS_LIST_LEN);
ESI_FSM_TYPE_IMPL(dev_fsm_t, int, int, STATE_LIST_LEN, EVENT_LIST_LEN, TRANS_LIST_LEN);

static ESI_FSM_STATE_T(dev_fsm_t) global_dev_fsm_initial_state = {.state_id = INITIAL_STATE, .state_mem = -1};
static ESI_FSM_DECL(dev_fsm_t, global_dev_fsm);

static void print_dev_fsm(dev_fsm_t *p_fsm);
static void print_dev_fsm(dev_fsm_t *p_fsm) {
    printf("[INFO]: current state is %d, counter = %d\n", p_fsm->current_state.state_id, p_fsm->current_state.state_mem);
}

static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, manifacture_trans, current_state, event, next_state);
static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, manifacture_trans, current_state, event, next_state) {
    next_state->state_id = FACTORY_STATE;
    next_state->state_mem = 0;
    return 0;
}

static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, authorize_trans, current_state, event, next_state);
static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, authorize_trans, current_state, event, next_state) {
    next_state->state_id = READY_STATE;
    return 0;
}

static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, withdraw_trans, current_state, event, next_state);
static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, withdraw_trans, current_state, event, next_state) {
    next_state->state_id = FACTORY_STATE;
    next_state->state_mem = 0;
    return 0;
}

static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, start_trans, current_state, event, next_state);
static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, start_trans, current_state, event, next_state) {
    next_state->state_id = WORKING_STATE;
    return 0;
}

static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, stop_trans, current_state, event, next_state);
static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, stop_trans, current_state, event, next_state) {
    next_state->state_id = READY_STATE;
    return 0;
}

static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, work_trans, current_state, event, next_state);
static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, work_trans, current_state, event, next_state) {
    next_state->state_mem += event->event_arg;
    return 0;
}

static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, default_trans, current_state, event, next_state);
static ESI_FSM_TRANS_FUNC_DECL(dev_fsm_t, default_trans, current_state, event, next_state) {
    printf("[ERROR]: illegal transition\n");
    return -1;
}

static void init_dev_fsm(dev_fsm_t *p_fsm);
static void init_dev_fsm(dev_fsm_t *p_fsm) {
    ESI_FSM_SET_CURRENT_STATE(dev_fsm_t, p_fsm, &global_dev_fsm_initial_state);

    ESI_FSM_ADD_STATE(dev_fsm_t, p_fsm, INITIAL_STATE);
    ESI_FSM_ADD_STATE(dev_fsm_t, p_fsm, FACTORY_STATE);
    ESI_FSM_ADD_STATE(dev_fsm_t, p_fsm, READY_STATE);
    ESI_FSM_ADD_STATE(dev_fsm_t, p_fsm, WORKING_STATE);
    
    ESI_FSM_ADD_EVENT(dev_fsm_t, p_fsm, INITIAL_STATE, MANU, manifacture_trans);
    ESI_FSM_ADD_EVENT(dev_fsm_t, p_fsm, FACTORY_STATE, AUTH, authorize_trans);
    ESI_FSM_ADD_EVENT(dev_fsm_t, p_fsm, READY_STATE, WITHDRAW, withdraw_trans);
    ESI_FSM_ADD_EVENT(dev_fsm_t, p_fsm, READY_STATE, START, start_trans);
    ESI_FSM_ADD_EVENT(dev_fsm_t, p_fsm, WORKING_STATE, STOP, stop_trans);
    ESI_FSM_ADD_EVENT(dev_fsm_t, p_fsm, WORKING_STATE, WORK, work_trans);

    ESI_FSM_SET_DEFAULT_TRANS(dev_fsm_t, p_fsm, default_trans);
}

int main(int argc, char *argv[]) {
    ESI_FSM_EVENT_T(dev_fsm_t) event;
    int ret;

    init_dev_fsm(&global_dev_fsm);
    print_dev_fsm(&global_dev_fsm);

    event.event_id = WORK;
    ret = ESI_FSM_TRANS(dev_fsm_t, &global_dev_fsm, &event);
    if (ret != 0) {
        printf("[ERROR]: %s\n", esi_fsm_strerror(ret));
    }
    print_dev_fsm(&global_dev_fsm);

    event.event_id = MANU;
    ret = ESI_FSM_TRANS(dev_fsm_t, &global_dev_fsm, &event);
    if (ret != 0) {
        printf("[ERROR]: %s\n", esi_fsm_strerror(ret));
    }
    print_dev_fsm(&global_dev_fsm);

    event.event_id = AUTH;
    ret = ESI_FSM_TRANS(dev_fsm_t, &global_dev_fsm, &event);
    if (ret != 0) {
        printf("[ERROR]: %s\n", esi_fsm_strerror(ret));
    }
    print_dev_fsm(&global_dev_fsm);

    event.event_id = START;
    ret = ESI_FSM_TRANS(dev_fsm_t, &global_dev_fsm, &event);
    if (ret != 0) {
        printf("[ERROR]: %s\n", esi_fsm_strerror(ret));
    }
    print_dev_fsm(&global_dev_fsm);

    event.event_id = WORK;
    event.event_arg = 5;
    ret = ESI_FSM_TRANS(dev_fsm_t, &global_dev_fsm, &event);
    if (ret != 0) {
        printf("[ERROR]: %s\n", esi_fsm_strerror(ret));
    }
    print_dev_fsm(&global_dev_fsm);

    event.event_id = WORK;
    event.event_arg = 3;
    ret = ESI_FSM_TRANS(dev_fsm_t, &global_dev_fsm, &event);
    if (ret != 0) {
        printf("[ERROR]: %s\n", esi_fsm_strerror(ret));
    }
    print_dev_fsm(&global_dev_fsm);

    event.event_id = STOP;
    ret = ESI_FSM_TRANS(dev_fsm_t, &global_dev_fsm, &event);
    if (ret != 0) {
        printf("[ERROR]: %s\n", esi_fsm_strerror(ret));
    }
    print_dev_fsm(&global_dev_fsm);

    printf("[INFO]: everything is fine.\n");
}