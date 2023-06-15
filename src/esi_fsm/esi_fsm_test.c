#include "esi_fsm.h"

#define INITIAL_STATE (0)
#define FACTORY_STATE (1)
#define READY_STATE (2)
#define WORKING_STATE (3)
#define STATE_LIST_LEN (4)
static esi_fsm_state_id_t state_list[STATE_LIST_LEN] = {
    INITIAL_STATE,
    FACTORY_STATE,
    READY_STATE,
    WORKING_STATE
};

struct fsm_state_memory {
    int counter;
};
static struct fsm_state_memory state_memory = {0};

#define MANU (0)
#define AUTH (1)
#define WITHDRAW (2)
#define START (3)
#define STOP (4)
#define WORK (5)
#define EVENT_LIST_LEN (6)
static esi_fsm_event_id_t event_list[EVENT_LIST_LEN] {
    MANU,
    AUTH,
    WITHDRAW,
    START,
    STOP,
    WORK
};

struct fsm_event_arg {
    int counter;
};

static int manu_trans(
    void *fsm_holder,
    struct esi_fsm_state current_state,
    struct esi_fsm_event event, 
    struct esi_fsm_state *next_state);
static int manu_trans(
    void *fsm_holder,
    struct esi_fsm_state current_state,
    struct esi_fsm_event event, 
    struct esi_fsm_state *next_state) {

    struct esi_fsm_from_lists *fsm = (struct esi_fsm_from_lists *) fsm_holder;
    
}

static esi_fsm_from_lists;

int main(int argc, char *argv[]) {
    
}