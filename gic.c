#include "peripheral_regs.h"

/**
 * Initializes the Generic Interrupt Controller, enabling the distributor and CPU interface,
 * as well as setting the priority mask to the supplied value.
**/
void gic_init(unsigned char mask) {
	/* Enable Distributor */
	*GICD_CTLR |= 1;
	/* Enable CPU Interface and set mask */
	*GICC_CTLR |= 1;
	*GICC_PMR |= mask;
}

/**
 * Enables the interrupt for the given ID with the supplied priority and targets
**/
void gic_enable_interrupt(unsigned int interrupt_id, unsigned char priority, unsigned char targets) {
	GICD_ISENABLER[interrupt_id / 32] |= 1 << (interrupt_id % 32);
	GICD_IPRIORITYR[interrupt_id / 4] |= priority << (8 * (interrupt_id % 4));
	GICD_ITARGETSR[interrupt_id / 4]  |= targets << (8 * (interrupt_id % 4));
}
