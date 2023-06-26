#include "esi_ring.h"

static const char *esi_ring_err_msg[] = ESI_RING_ERR_MSG;

const char *esi_ring_strerror(int err) {
    return esi_ring_err_msg[err];
}
