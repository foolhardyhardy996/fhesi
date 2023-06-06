#pragma once 

/**
 * @file esi_uart.h
 * @brief "esi_uart.h" provides platform-independent interfaces for common UART 
 * operations.
 * 
 * Please provide the concrete implementation for these interfaces for your
 * platform.
 * 
 * @author Li Weida
 * @date 2023.05.26
 * 
*/

#include "esi_common/esi_err.h"

/**
 * `esi_uart_port_t` is used to refer available UART ports.
 * 
*/
typedef int esi_uart_port_t;

/**
 * if there are multiple UART port avaliable, they are referred by the 
 * following macros, they are of `esi_uart_port_t` type:
 * ESI_UART_PORT1
 * ESI_UART_PORT2
 * ...
*/

/**
 * @brief check if "esi_uart" module is avaliable on underlying platform
 * 
 * @return non-zero value if it's available, or zero if not
*/
int esi_uart_available(void);

/**
 * @brief get the number of available UART port on underlying platform
 * 
 * There are two ways to get the reference to available UART ports:
 * 1. check "esi_uart.h" header file for `ESI_UART_PORT*`
 * 2. call `esi_uart_get_port_num()` then call `esi_uart_get_port_by_id()`
 * accordingly.
 * 
 * @return the number of available ports
*/
int esi_uart_get_port_num(void);

#ifdef ESI_PLATFORM_FEATURES_UART_AVAILABLE

/**
 * @brief get `ESI_UART_PORT<id>`
*/
esi_uart_port_t esi_uart_get_port_by_id(int id);

/**
 * @brief check if the given port is open
 * 
 * @return non-zero value if it's open or zero if not
*/
int esi_uart_is_open(esi_uart_port_t port);

esi_err_t esi_uart_open(esi_uart_port_t port);

esi_err_t esi_uart_close(esi_uart_port_t port);

esi_err_t esi_uart_rx_ready(esi_uart_port_t port);

esi_err_t esi_uart_tx_ready(esi_uart_port_t port);

esi_err_t esi_uart_putchar(esi_uart_port_t port, uint8_t c);

esi_err_t esi_uart_getchar(esi_uart_port_t port, uint8_t *c);

#endif