#pragma once

#include "esi_logdev.h"

/**
 * @file esi_logger.h
 * @brief "logger" provide common logging utility functions, which write log 
 * into underlying "logdev"
 * 
 * The main purpose of "logger" is to provide "device-independent" logging 
 * utilities alongwith formatting.
 * 
 * @author Li Weida
 * @date 2023.05.16
*/

#define LOGGER_MAX_LOGDEV_NUM (4)
struct logger {
    /**< the blob hiding the configuration details or implementation-defined 
     * details */
    void *logger_struct;
    /**< the underlying "log_device"s */
    struct esi_logdev logdev_array[LOGGER_MAX_LOGDEV_NUM];
    int logdev_num;
    char prefix[64];
};

/**
 * @brief set the prefix of the following log the logger will write
 * 
 * @return a status code indicating whether it succeeded or what error 
 * occured
*/
int esi_logger_set_prefix(struct esi_logger *logger, const char *prefix);

/**
 * @brief add one more "logdev" 
 * 
 * @return a status code indicating whether it succeeded or what error 
 * occured
*/
int esi_logger_add_logdev(struct esi_logger *logger, struct esi_logdev *logdev);

/**
 * @brief just like std printf, but write log to each "logdev" belonging to
 * "logger"
 * 
 * @return a status code indicating whether it succeeded or what error 
 * occured
*/
int esi_logger_printf(struct esi_logger *logger, const char *fmt, ...);

extern struct esi_logger *default_logger;

/**
 * @brief close previous "default_logger", set "logger" to "default_logger"
*/
void esi_set_default_logger(struct esi_logger *logger);

/**
 * @brief just like "esi_logger_printf" but take the "default_logger"
 * 
 * @return a status code indicating whether it succeeded or what error 
 * occured
*/
int esi_printf(const char *fmt, ...);