#include "esi_rrserver.h"
#include "esi_err/esi_err.h"

static const char *esi_rrserver_err_msg[] = ESI_RRSERVER_ERR_MSG;

const char *esi_rrserver_strerror(esi_err_t err) {
    return esi_rrserver_err_msg[err];
}