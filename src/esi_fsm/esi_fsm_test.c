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

static ESI_FSM_STATE_T(dev_fsm_t) global_dev_fsm_initial_state = {.state_id = INITIAL_STATE, .state_mem = 0};
static ESI_FSM_DECL(dev_fsm_t, global_dev_fsm);

static void print_dev_fsm(dev_fsm_t *p_fsm);
static void print_dev_fsm(dev_fsm_t *p_fsm) {
    printf("[INFO]: current state is %d, counter = %d\n", p_fsm->current_state.state_id, p_fsm->current_state.state_mem);
}

static void init_dev_fsm(dev_fsm_t *p_fsm) {
    ESI_FSM_SET_CURRENT_STATE(dev_fsm_t, p_fsm, &global_dev_fsm_initial_state);
}

int main(int argc, char *argv[]) {
    init_dev_fsm(&global_dev_fsm);
    print_dev_fsm(&global_dev_fsm);
    printf("[INFO]: everything is fine.\n");
}