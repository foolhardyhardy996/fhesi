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

/**
 * Related types of finite state machine:
 * 1. fsm_state = state_id + state_memory
 * 2. fsm_event = event_id + event_arg
 * 3. fsm_trans_func = (current_state, event) -> next_state
 * 4. fsm_trans = fsm_trans_func + (state_id, event_id)
 * 5. 
*/
#define ESI_FSM_TYPE_DECL(STATE_MEM_T, EVENT_ARG_T) \
