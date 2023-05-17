#pragma once

#include "log_device.h"

/**
 * @file logger.h
 * @brief "logger" provide common logging utility functions, which write log 
 * into underlying "log_device"
 * 
 * The main purpose of "logger" is to provide "device-independent" logging 
 * utilities alongwith formatting.
 * 
 * @author Li Weida
 * @date 2023.05.16
*/

struct logger_ops {
    /**
     * @brief set the prefix of the following log records
     * 
     * @return a status code indicating whether it succeeded or what error 
     * occured
    */
    int (*set_prefix)(struct logger *lggr, const char *prefix);

    /**
     * @brief add one more logging device
     * 
     * @return a status code indicating whether it succeeded or what error 
     * occured
    */
    int (*add_logdev)(struct logger *lggr, struct log_device *logdev);
};

#define LOGGER_MAX_LOGDEV_NUM (4)
struct logger {
    /**< the blob hiding the configuration details or implementation-defined 
     * details */
    void *logger_struct;
    /**< the underlying "log_device"s */
    struct log_device logdev_array[LOGGER_MAX_LOGDEV_NUM];
    int logdev_num;
    char prefix[64];
};

/**
 * @brief set the prefix of the following log the logger will write
 * 
 * @return a status code indicating whether it succeeded or what error 
 * occured
*/
int logger_set_prefix(struct logger *lggr, const char *prefix);

/**
 * @brief add one more "log_device" 
 * 
 * @return a status code indicating whether it succeeded or what error 
 * occured
*/

/**
 * @brief just like std printf, but write log to each "log_dev" belonging to
 * "lggr"
 * 
 * @return a status code indicating whether it succeeded or what error 
 * occured
*/
int logger_printf(struct logger *lggr, const char *fmt, ...);

extern struct logger *default_lggr;

/**
 * @brief close previous "default_lggr", set "lggr" to "default_lggr"
*/
void set_default_logger(struct logger *lggr);

/**
 * @brief just like "logger_printf" but take the "default_lggr"
 * 
 * @return a status code indicating whether it succeeded or what error 
 * occured
*/
int dflt_printf(const char *fmt, ...);