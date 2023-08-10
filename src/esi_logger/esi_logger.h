#pragma once 

/**
 * @file esi_logger.h
 * @brief esi_logger provide a logger class which bridges between logging 
 * interfaces and backend logging device or mechanism.
 * 
 * @author Li Weida
 * @date 2023.08.09
*/

#include "esi_err/esi_err.h"
#include "esi_fmt/esi_fmt.h"
#include <stdarg.h>

enum esi_logger_err {
    ESI_LOGGER_ERR_NONE = 0,
    ESI_LOGGER_ERR_INVALID = 1
};

#define ESI_LOGGER_ERR_MSG {\
    "esi_logger: ok", /*0*/\
    "esi_logger: invalid argument" /*1*/\
}

const char *esi_logger_strerror(int err);

#define ESI_LOGGER_DECL(alias, config_t) \
typedef config_t alias##_config_t;\
typedef void (*alias##_write_func_t)(char *, int);\
typedef int (*alias##_filter_func_t)(config_t *);\
typedef const char *(*alias##_prefix_func_t)(config_t *);\
struct alias##_logger {\
    alias##_write_func_t write;\
    alias##_filter_func_t filter;\
    alias##_prefix_func_t prefix;\
};\
typedef struct alias##_logger alias;\
esi_err_t alias##_init(alias *, alias##_write_func_t, alias##_filter_func_t, alias##_prefix_func_t);\
esi_err_t alias##_logf(alias *, config_t *, const char *, ...);

#define ESI_LOGGER_IMPL(alias, config_t) \
static int alias##_default_filter(config_t *);\
static int alias##_default_filter(config_t *foo) {\
    return 0;\
}\
static const char *alias##_default_prefix(config_t *);\
static const char *alias##_default_prefix(config_t *foo) {\
    return "";\
}\
esi_err_t alias##_init(alias *self, alias##_write_func_t write, alias##_filter_func_t filter, alias##_prefix_func_t prefix) {\
    if (write == NULL) {\
        return ESI_LOGGER_ERR_INVALID;\
    }\
    self->write = write;\
    if (filter == NULL) {\
        self->filter = alias##_default_filter;\
    } else {\
        self->filter = filter;\
    }\
    if (prefix == NULL) {\
        self->prefix = alias##_default_prefix;\
    } else {\
        self->prefix = prefix;\
    }\
    return ESI_LOGGER_ERR_NONE;\
}\
esi_err_t alias##_logf(alias *self, config_t *config, const char *fmt, ...) {\
    va_list va;\
    int n, m;\
    char buffer[256];\
    if (!self->filter(config)) {\
        n = esi_snprintf(buffer, 256, "%s", self->prefix(config));\
        if (n < 0) {\
            n = 0;\
        }\
        va_start(va, fmt);\
        m = esi_vsnprintf(buffer + n, 254-n, fmt, va);\
        if (m > 0) {\
            if (buffer[n+m-1] != '\n') {\
                buffer[n+m] = '\n';\
                buffer[n+m+1] = 0;\
            } else {\
                buffer[n+m] = 0;\
            }\
        }\
        va_end(va);\
        self->write(buffer, n+m);\
    }\
    return ESI_LOGGER_ERR_NONE;\
}
