#include <stdarg.h>
#include <stdbool.h>
#include "peripheral_regs.h"
#include "uart.h"

static inline bool tx_full(void) {
	return (*UART_CHANNEL_STS_REG0 & (1 << 4)) >> 4;
}

/**
 * Transmits the given character through the UART.
**/
void uart_putc(char c) {
	while (tx_full());	// Busy wait while the TX buffer is full
	*(char*)UART_TX_RX_FIFO0 = c;
}

/**
 * Transmits the given null-terminated string through the UART, without its terminating null byte '\0'.
 * Returns the number of characters written.
**/
int uart_puts(const char* s) {
	char c;
	int counter = 0;

	while ((c = *s++)) {
		while (tx_full());	// Busy wait while the TX buffer is full
		*(char*)UART_TX_RX_FIFO0 = c;
		counter++;
	}

	return counter;
}

#define PREFIX 	    (1 << 4)
#define ZERO_PAD  	(1 << 3)
#define LEFT_ADJUST	(1 << 2)
#define BLANK_POS 	(1 << 1)
#define PLUS_POS  	(1 << 0)


static int utoa(unsigned int n, char* dest, int base) {
	char buffer[64] = {0};
	register int i = 0;
	register int r;
	do {
		r = n % base;
		buffer[i++] = (r < 10) ? r + '0' : (r - 10) + 'a';
		n /= base;
	} while (n);

	for (register int j = 0; j < i; j++) {
		dest[j] = buffer[i - 1 - j];
	}
	dest[i] = '\0';

	return i;
}


static int print_number(int is_signed, unsigned int n, int base, const char* prefix, int width, int flags) {
	int counter;
	register int i;
	char sign = 0;
	char buffer[64] = {0};

	if (is_signed) {
		counter = utoa(((signed int) n < 0) ? -n : n, buffer, base);
		if ((signed int)n < 0) {
			sign = '-';
		} else if (flags & PLUS_POS) {
			sign = '+';
		} else if (flags & BLANK_POS) {
			sign = ' ';
		}
	} else {
		counter = utoa(n, buffer, base);
	}

	if (flags & LEFT_ADJUST) {
		if (sign) {
			uart_putc(sign);
			counter++;
		}
		if (flags & PREFIX) {
			counter += uart_puts(prefix);
		}
		uart_puts(buffer);
		for (i = counter; i < width; i++) {
			uart_putc(' ');
			counter++;
		}
	} else {
		if (flags & PREFIX) {
			for (i = 0; prefix[i]; i++) {
				counter++;
			}
		}

		if (flags & ZERO_PAD) {
			if (sign) {
				uart_putc(sign);
				counter++;
			}
			if (flags & PREFIX) {
				uart_puts(prefix);
			}
			for (i = counter; i < width; i++) {
				uart_putc('0');
				counter++;
			}
		} else {
			for (i = counter; i < width; i++) {
				uart_putc(' ');
				counter++;
			}
			if (sign) {
				uart_putc(sign);
				counter++;
			}
			if (flags & PREFIX) {
				uart_puts(prefix);
			}
		}
		uart_puts(buffer);
	}
	return counter;
}


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
int uart_printf(const char* restrict format, ...) {
	va_list args;
	char character;
	int checking_flags;
	int counter = 0;
	int flags;
	int width;

	int i;
	unsigned int u;
	char c;
	char* s;

	if (format == 0) {
		return 0;
	}

	va_start(args, format);

	while ((character = *format++)) {
		if (character != '%') {
			uart_putc(character);
			counter++;
			continue;
		}

		/* Flags */
		checking_flags = 1;
		flags = 0;
		while (checking_flags) {
			character = *format++;
			switch (character) {
			case '#':
				flags |= PREFIX;
				break;
			case '0':
				flags |= ZERO_PAD;
				break;
			case '-':
				flags |= LEFT_ADJUST;
				break;
			case ' ':
				flags |= BLANK_POS;
				break;
			case '+':
				flags |= PLUS_POS;
				break;
			default:
				checking_flags = 0;
				break;
			}
		}

		/* Width */
		width = 0;
		while (character >= '0' && character <= '9') {
			width = width * 10 + (character - '0');
			character = *format++;
		}

		/* Conversion */
		switch (character) {
		case 'd':
		case 'i':
			i = va_arg(args, int);
			counter += print_number(1, i, 10, "", width, flags);
			break;
		case 'b':
			u = va_arg(args, unsigned int);
			counter += print_number(0, u, 2, "0b", width, flags);
			break;
		case 'o':
			u = va_arg(args, unsigned int);
			counter += print_number(0, u, 8, "0o", width, flags);
			break;
		case 'u':
			u = va_arg(args, unsigned int);
			counter += print_number(0, u, 10, "", width, flags);
			break;
		case 'x':
			u = va_arg(args, unsigned int);
			counter += print_number(0, u, 16, "0x", width, flags);
			break;
		case 'p':
			u = va_arg(args, unsigned int);
			counter += print_number(0, u, 16, "0x", (width < 10) ? 10 : width, flags | PREFIX | ZERO_PAD);
			break;
		case 'c':
			c = (char) va_arg(args, int);
			uart_putc(c);
			counter++;
			break;
		case 's':
			s = va_arg(args, char*);
			counter += uart_puts(s ? s : "(null)");
			break;
		case '%':
			uart_putc('%');
			counter++;
			break;
		default:
			break;
		}
	}

	va_end(args);
	return counter;
}
