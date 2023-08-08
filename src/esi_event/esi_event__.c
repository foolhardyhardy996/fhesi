#include "esi_event.h"

static const char *esi_event_err_msg[] = ESI_EVENT_ERR_MSG;

const char *esi_event_strerror(int err) {
    return esi_event_err_msg[err];
}

int esi_event_handler_init(esi_event_handler_t *p_handler, int handler_id, int event_id, esi_event_handler_func_t handler_func) {
    p_handler->handler_id = handler_id;
    p_handler->event_id = event_id;
    p_handler->handler_func = handler_func;
    
    return ESI_EVENT_ERR_NONE;
}