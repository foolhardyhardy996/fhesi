#include "esi_sdlist.h"

static const char *esi_sdlist_err_msg[] = ESI_SDLIST_ERR_MSG;

const char *esi_sdlist_strerror(int err) {
    return esi_sdlist_err_msg[err];
}
