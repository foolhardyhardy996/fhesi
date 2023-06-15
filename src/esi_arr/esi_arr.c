#include "esi_arr.h"

static const char *esi_arr_err_msg[] = ESI_ARR_ERR_MSG;

const char *esi_arr_strerror(int err) {
    return esi_arr_err_msg[err];
}
