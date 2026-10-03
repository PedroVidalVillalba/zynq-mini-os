#ifndef PRIVATE_TIMER_H
#define PRIVATE_TIMER_H

#include <stdbool.h>

/**
 * Starts the Private Timer with the given load and prescaler values, setting
 * auto reload and IRQ signaling according to the passed arguments.
 **/
void private_timer_start(unsigned int load, unsigned char prescaler,
                         bool autoreload, bool irq_enable);

/**
 * Stops the Private Timer.
 **/
void private_timer_stop(void);

/**
 * Checks the Private Timer status.
 * If clear is set to true, it also clears the status sticky bit if it was set.
 * Returns the status bit.
 *
 **/
bool private_timer_status(bool clear);

/**
 * Generic ISR for the Private Timer.
 * Delegates the functionality to the supplied callback function, and clears the
 * status sticky bit when done.
 **/
void private_timer_isr(void (*callback)(void));

#endif // PRIVATE_TIMER_H
