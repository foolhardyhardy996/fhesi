#pragma once 

/**
 * @file esi_uart.h
 * @brief "esi_uart" provides platform-specific implementation for common UART 
 * operations.
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.05.26
 * 
*/

int esi_uart_available(void);

int esi_uart_get_num(void);

#ifdef ESI_PLATFORM_FEATURES_UART_AVAILABLE

struct esi_uart {
    /* platform-specific implementation of esi_uart */
};

int esi_uart_open(struct esi_uart *uart, int id);

int esi_uart_close(struct esi_uart *uart);

int esi_uart_rx_ready(struct esi_uart *uart);

int esi_uart_tx_ready(struct esi_uart *uart);

int esi_uart_putchar(struct esi_uart *uart, char c);

int esi_uart_getchar(struct esi_uart *uart, char *c);

#endif