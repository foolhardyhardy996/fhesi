#include "esi_err.h"
#include "esi_str.h"

static const char *esi_err_src_msg[] = ESI_ERR_SRC_MSG;

static const char *esi_err_status_msg[] = ESI_ERR_STATUS_MSG;

const char *esi_strerror(esi_err_t err) {
    static char buffer[ESI_STRERROR_BUFSIZE];
    strncpy(buffer, esi_err_src_msg[ESI_ERR_SRC_PART(err)], ESI_STRERROR_BUFSIZE);
    strncat(buffer, ": ", ESI_STRERROR_BUFSIZE);
    strncat(buffer, esi_err_status_msg[ESI_ERR_STATUS_PART(err)], ESI_STRERROR_BUFSIZE);
    return buffer;
}