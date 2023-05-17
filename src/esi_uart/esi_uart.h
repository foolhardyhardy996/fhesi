#pragma once 

/**
 * @file esi_uart.h
 * @brief "esi_uart" abstract out those common interfaces any UART hardware 
 * should provide. The concrete implementation is hardware-specific.
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.05.17
*/

struct uart_ops {
    int (*open)(struct esi_uart *uart, void *arg);
    int (*close)(struct esi_uart *uart, void *arg);
    int (*rx_ready)(struct esi_uart *uart);
    int (*tx_ready)(struct esi_uart *uart);
    int (*putchar)(struct esi_uart *uart, char c);
    int (*getchar)(struct esi_uart *uart, char *c);
};

struct esi_uart {
    /**< the blob hiding the details of each uart device */
    void *uart_struct;

    /**< concrete implementations are encapsulated in "uart_ops" */
    struct uart_ops *ops;
};

int esi_uart_open(struct esi_uart *uart, void *arg);

int esi_uart_close(struct esi_uart *uart, void *arg);

int esi_uart_rx_ready(struct esi_uart *uart);

int esi_uart_tx_ready(struct esi_uart *uart);

int esi_uart_putchar(struct esi_uart *uart, char c);

int esi_uart_getchar(struct esi_uart *uart, char *c);
