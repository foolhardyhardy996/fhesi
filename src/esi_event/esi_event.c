#include "esi_event.h"

static const char *esi_event_err_msg[] = ESI_EVENT_ERR_MSG;

const char *esi_event_strerror(int err) {
    return esi_event_err_msg[err];
}
