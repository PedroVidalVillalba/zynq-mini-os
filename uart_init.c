#include "peripheral_regs.h"
#include "uart.h"

#define CHMODE_NORMAL 			(0b00 << 8)
#define CHMODE_AUTOMATIC_ECHO 	(0b01 << 8)
#define CHMODE_LOCAL_LOOPBACK	(0b10 << 8)
#define CHMODE_REMOTE_LOOPBACK	(0b11 << 8)

#define NBSTOP_1				(0b00 << 6)
#define NBSTOP_1_5				(0b01 << 6)
#define NBSTOP_2				(0b10 << 6)

#define PAR_EVEN				(0b000 << 3)
#define PAR_ODD					(0b001 << 3)
#define PAR_FORCED_0			(0b010 << 3)
#define PAR_FORCED_1			(0b011 << 3)
#define PAR_NO_PARITY			(0b100 << 3)

#define CHRL_6					(0b11 << 1)
#define CHRL_7					(0b10 << 1)
#define CHRL_8					(0b00 << 1)

#define CLKSEL_REF_CLK			(0b0 << 0)
#define CLKSEL_REF_CLK_DIV_8	(0b1 << 0)


#define STOPBRK					(1 << 8)
#define STARTNRK				(1 << 7)
#define TO_RST					(1 << 6)
#define TX_DIS					(1 << 5)
#define TX_EN					(1 << 4)
#define RX_DIS					(1 << 3)
#define RX_EN					(1 << 2)
#define TX_RST					(1 << 1)
#define RX_RST					(1 << 0)

/**
 * Initializes the UART connection, setting the UART to Normal mode,
 * 1-bit stop, 8-bit packages, no parity check and baud rate of 115 200 bps.
**/
void uart_init(void) {
	/* 1. Configure UART packet format */
	// Normal mode, 1 stop bit, 8-bit, bit[5:3] = No Parity (1xx)
	*UART_MODE_REG0 = CHMODE_NORMAL | NBSTOP_1 | PAR_NO_PARITY | CHRL_8 | CLKSEL_REF_CLK;

	/* 2. Configure the Baud Rate to 115,200bps and Enable UART */
	// 2.1. Disable RX and TX
	*UART_CONTROL_REG0 |= TX_DIS | RX_DIS;
	// 2.2. Write the calculated CD value and BDIV for 115,200bps
	// 115,207 bps = 50 MHz / (62 * (6 + 1))
	*UART_BAUD_RATE_GEN_REG0 = 62;
	*UART_BAUD_RATE_DIVIDER_REG0 = 6;
	// 2.3. Reset TX and RX
	*UART_CONTROL_REG0 |= TX_RST | RX_RST;
	// 2.4. Enable Rx and TX
	*UART_CONTROL_REG0 &= ~(TX_DIS | RX_DIS);
	*UART_CONTROL_REG0 |= TX_EN | RX_EN;

	/* 3. Enable the Controller */
	*UART_CONTROL_REG0 = STOPBRK | TX_EN | RX_EN | TX_RST | RX_RST;
}
