#include "esi_vlbqueue.h"
#include "esi_err/esi_err.h"

static const char *esi_vlbqueue_err_msg[] = ESI_VLBQUEUE_ERR_MSG;

const char *esi_vlbqueue_strerror(esi_err_t err) {
    return esi_vlbqueue_err_msg[err];
}