#include <stddef.h>

#include "esi_fsm.h"

static struct esi_fsm_trans *search_trans(
    struct esi_fsm_trans *trans_list, 
    int trans_list_len,
    esi_fsm_state_id_t state_id,
    esi_fsm_event_id_t event_id);

static struct esi_fsm_trans *search_trans(
    struct esi_fsm_trans *trans_list, 
    int trans_list_len,
    esi_fsm_state_id_t state_id,
    esi_fsm_event_id_t event_id) {
    struct esi_fsm_trans *target = NULL;
    int i = 0;

    for(i = 0; i < trans_list_len; i++) {
        if (state_id == trans_list[i].state_id && event_id == trans_list[i].event_id) {
            target = &(trans_list[i]);
            break;
        }
    }

    return target;
}

int esi_fsm_from_lists_trans(
    void *fsm_holder,
    struct esi_fsm_state current_state,
    struct esi_fsm_event event, 
    struct esi_fsm_state *next_state) {

    struct esi_fsm_from_lists *fsm = (struct esi_fsm_from_lists *) fsm_holder;
    esi_fsm_state_id_t current_state_id = current_state.state_id;
    esi_fsm_event_id_t event_id = event.event_id;
    struct esi_fsm_trans *dedicated_trans = search_trans(
        fsm->trans_list, 
        fsm->trans_list_len, 
        current_state_id, 
        event_id);
    if (dedicated_trans == NULL) {
        return fsm->null_trans(fsm_holder, current_state, event, next_state);
    } else {
        return dedicated_trans->trans(fsm_holder, current_state, event, next_state);
    }

} 

int esi_fsm_create_from_lists(
    struct esi_fsm_from_lists *fsm,
    esi_fsm_state_id_t *state_list,
    int state_list_len,
    esi_fsm_event_id_t *event_list,
    int event_list_len,
    struct esi_fsm_trans *trans_list,
    int trans_list_len,
    esi_fsm_trans_func_t null_trans,
    struct esi_fsm_state initial_state) {

    fsm->state_list = state_list;
    fsm->state_list_len = state_list_len;
    fsm->event_list = event_list;
    fsm->event_list_len = event_list_len;
    fsm->trans_list = trans_list;
    fsm->trans_list_len = trans_list_len;
    fsm->null_trans = null_trans;
    fsm->trans = esi_fsm_from_lists_trans;
    fsm->current_state = initial_state;

    return 0;
}

