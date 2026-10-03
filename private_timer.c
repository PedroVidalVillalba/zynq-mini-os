#include <stdbool.h>
#include "peripheral_regs.h"
#include "private_timer.h"

#define IRQ_ENABLE		(1 << 2)
#define AUTO_RELOAD		(1 << 1)
#define TIMER_ENABLE	(1 << 0)

/**
 * Starts the Private Timer with the given load and prescaler values, setting auto reload and IRQ signaling according to the passed arguments.
**/
void private_timer_start(unsigned int load, unsigned char prescaler, bool autoreload, bool irq_enable) {
	*PRIVATE_LOAD = load;
	*PRIVATE_CONTROL = (prescaler << 8) | (autoreload ? AUTO_RELOAD : 0) | (irq_enable ? IRQ_ENABLE : 0) | TIMER_ENABLE;
}

/**
 * Stops the Private Timer.
**/
void private_timer_stop(void) {
	*PRIVATE_CONTROL &= ~TIMER_ENABLE;
}

/**
 * Checks the Primate Timer status.
 * If clear is set to true, it also clears the status sticky bit if it was set.
 * Returns the status bit.
 *
**/
bool private_timer_status(bool clear) {
	register bool status = *PRIVATE_STATUS;
	if (status && clear) *PRIVATE_STATUS = 1;
	return status;
}

/**
 * Generic ISR for the Private Timer.
 * Delegates the functionality to the supplied callback function, and clears the status sticky bit when done.
**/
void private_timer_isr(void (*callback)(void)) {
	callback();
	*PRIVATE_STATUS = 1;
}
