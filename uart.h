#ifndef UART_H
#define UART_H

/**
 * Initializes the UART connection, setting the UART to Normal mode,
 * 1-bit stop, 8-bit packages, no parity check and baud rate of 115 200 bps.
**/
void uart_init(void);

/**
 * Transmits the given character through the UART.
**/
void uart_putc(char c);

/**
 * Transmits the given null-terminated string through the UART, without its terminating null byte '\0'.
 * Returns the number of characters written.
**/
int uart_puts(const char* s);

/**
 * Transmits a formatted string to the UART from the given format string and the arguments provided.
 * Provides a subset of the functionality from standard printf function.
 * Supported formats: %[flags][width]conversion, where flags are the ones specified in the POSIX specification, width is a non negative
 * number specifying the minimum number of characters to fill with and integer, and conversion can be:
 * 		d, i		Print signed, decimal integers
 * 		b, o, u, x	Print unsigned integers, in base 2, 8, 10 and 16, respectively
 * 		c			Print a character
 * 		s			Print a null-terminated string
 * 		p			Print a pointer
 * 		%			Print a literal '%' character
 * Returns the total number of characters written.
**/
int uart_printf(const char* restrict format, ...);

#endif // UART_H
