#include "esi_logger.h"
#include <stdio.h>

typedef const int log_level_t;
const log_level_t log_level_debug = 0;
const log_level_t log_level_info = 1;
const log_level_t log_level_notice = 2;
const log_level_t log_level_error = 3;
#define SHELL_LOGGER_DEBUG  (&log_level_debug)
#define SHELL_LOGGER_INFO   (&log_level_info)
#define SHELL_LOGGER_NOTICE (&log_level_notice)
#define SHELL_LOGGER_ERROR  (&log_level_error)
ESI_LOGGER_DECL(shell_logger_t, log_level_t)
ESI_LOGGER_IMPL(shell_logger_t, log_level_t)

static void shell_logger_write(char *, int);
static void shell_logger_write(char *s, int len) {
    printf("%s", s);
}

static int shell_logger_filter_debug(log_level_t *);
static int shell_logger_filter_debug(log_level_t *log_level) {
    if (*log_level > log_level_debug) {
        return 0;
    } else {
        return 1;
    }
}

static const char *shell_logger_prefix(log_level_t *);
static const char *shell_logger_prefix(log_level_t *log_level) {
    switch (*log_level) {
    case log_level_debug:
        return "[DEBUG]: ";
    case log_level_info:
        return "[INFO]: ";
    case log_level_notice:
        return "[NOTICE]: ";
    case log_level_error:
        return "[ERROR]: ";
    default:
        return "[UNKNOWN]: ";
    }
}

static shell_logger_t logger;

int main(int argc, char *argv[]) {
    shell_logger_t_init(&logger, shell_logger_write, shell_logger_filter_debug, shell_logger_prefix);
    shell_logger_t_logf(&logger, SHELL_LOGGER_INFO, "Hello, %s!", "World");
    shell_logger_t_logf(&logger, SHELL_LOGGER_DEBUG, "You should not see this message!");
    shell_logger_t_logf(&logger, SHELL_LOGGER_ERROR, "1 + 1 = %d", 11);
    return 0;
}