#include "esi_logger.h"

static const char *esi_logger_err_msg[] = ESI_LOGGER_ERR_MSG;

const char *esi_logger_strerror(int err) {
    return esi_logger_err_msg[err];
}
