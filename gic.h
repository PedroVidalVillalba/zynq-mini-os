#ifndef GIC_H
#define GIC_H

/**
 * Initializes the Generic Interrupt Controller, enabling the distributor and CPU interface,
 * as well as setting the priority mask to the supplied value.
**/
void gic_init(unsigned char mask);


/**
 * Enables the interrupt for the given ID with the supplied priority and targets
**/
void gic_enable_interrupt(unsigned int interrupt_id, unsigned char priority, unsigned char targets);


#endif // GIC_H
