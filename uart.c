#include "uart.h"

#define UART_BASE 0x10000000
#define UART_THR  (*(volatile char *)(UART_BASE + 0x00)) // Transmit Holding Register
#define UART_RBR  (*(volatile char *)(UART_BASE + 0x00)) // Receive Buffer Register
#define UART_LSR  (*(volatile char *)(UART_BASE + 0x05)) // Line Status Register

#define UART_LSR_TX_IDLE  (1 << 5) // Transmitter idle
#define UART_LSR_RX_READY (1 << 0) // Receiver ready

void uart_putc(char c) {
    while ((UART_LSR & UART_LSR_TX_IDLE) == 0);
    UART_THR = c;
    
    if (c == '\n') {
        while ((UART_LSR & UART_LSR_TX_IDLE) == 0);
        UART_THR = '\r';
    }
}

char uart_getc(void) {
    while ((UART_LSR & UART_LSR_RX_READY) == 0);
    return UART_RBR;
}

