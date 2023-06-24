#include <stddef.h>
#include "esi_fsm.h"

static const char *esi_fsm_err_msg[] = ESI_FSM_ERR_MSG;

const char *esi_fsm_strerror(int err) {
    return esi_fsm_err_msg[err];
}