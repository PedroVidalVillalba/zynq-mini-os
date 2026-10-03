#include "gic.h"
#include "peripheral_regs.h"
#include "private_timer.h"
#include "process.h"
#include "uart.h"

extern int task1_c();
extern int task2_c();
extern int task3_c();

/**
 * Initializes the GIC, the UART, the Private Timer and sets up the user
 * programs
 **/
void init(void) {
    uart_init();
    gic_init(0xff); // Set mask to max value so as not to mask interrupts
    gic_enable_interrupt(29, 0x10,
                         0xff); // Enable interrupts from private timer (ID
                                // #29), with priority 16 and for all CPUs

    process_new(task1_c);
    process_new(task2_c);
    process_new(task3_c);

    // Prescaler value = 166 => T = (prescaler + 1) / PERIPHCLK = (166 + 1) /
    // (333.333 MHz) = 0.5us load = 2_000 => T * load = 1 ms Auto reload and IRQ
    // enabled
    private_timer_start(2000, 166, true, true);
}

/**
 * Schedules a process for execution following a round-robin mechanism
 **/
void scheduler(void) {
    static pid_t process = 0;
    process_execute(process + 1);
    process = (process + 1) % 3; // round robin: task1 -> task2 -> task3 ->
                                 // task1 -> task2 -> task3 -> ...
}

/**
 * Interrupt Service Routine main body for IRQ signal
 **/
void irq_isr(void) {
    int interrupt_ack =
        *GICC_IAR; // Get interrupt ID from the acknowledge register

    // Distribute to the corresponding specific ISR based on ID of the IRQ
    switch (interrupt_ack) {
    case 29: // Only one supported
        private_timer_isr(scheduler);
        break;
    default:
        break;
    }

    *GICC_EOIR =
        interrupt_ack; // Inform to the GIC of the end of the interrupt handling
}
