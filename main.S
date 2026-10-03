.extern init
.extern irq_isr

.global main
.global user_stack_top
.global saved_state

/* Custom event vector table */
.align 5
vector_table:
    b .
    b .
    b .
    b .
    b .
    b .
    b IRQ_ISR
    b .



main:
    // Disable interrupts: CPSR'I = 1
    cpsid i

    cps #0x12               // IRQ mode
    ldr r13, =irq_stack_top // stack pointer setup for IRQ mode

    cps #0x13               // Supervisor mode
    ldr r13, =svc_stack_top // stack pointer setup for SVC mode

    // Set VBAR (Vector Base Address Register) to my vector table
    ldr     r0, =vector_table
    mcr     p15, 0, r0, c12, c0, 0
    dsb
    isb

    bl init     // call init routine in C

    cpsie i, #0x10   // enable interrupts and change to user mode for executing the programs

    // Nothing left to do, just wait for the interrupts
    forever:
        nop
        wfi     // wait for interrupt, to avoid wasting resources busy waiting
        b forever


IRQ_ISR:
    /* Save the state of the process being interrupted to saved_state */
    str r0, [sp, #-4]!      // temporarily save r0 to the IRQ stack, since we need one register to point to saved_state
    ldr r0, =saved_state    // load into r0 the address where we will save the program state
    add r0, r0, #4          // adjust r0 position to save r1-r14 from the user process
    stm r0, {r1-r14}^       // save user registers r1-r14 to saved_state
    ldr r1, [sp], #4        // pop back the value of r0
    str r1, [r0, #-4]!      // save the value of r0 to saved_state
    sub r1, lr, #4          // calculate the address of the next instruction to execute by the user process (previous instruction to the one stored in IRQ link register)
    str r1, [r0, #4*15]     // save user program counter to saved_state
    mrs r1, SPSR            // get the status register for the interrupted process (stored in SPSR)
    str r1, [r0, #4*16]     // save the status register to saved_state

    bl irq_isr          // actual handler implemented in C

    /* Restore the state of the user process from saved_state (after scheduling, the process to restored will be different than the one saved) */
    ldr r0, =saved_state    // load into r0 the address from which to recover the program state
    ldr r1, [r0, #4*16]     // load the status register from saved_state
    msr SPSR_all, r1        // restore SPSR to the status register from saved_state
    ldr lr, [r0, #4*15]     // load the program counter to return to from saved_state to the IRQ link register
    ldm r0, {r0-r14}^       // load all the general purpose register r0-r14 of user mode from saved_state

    movs pc, lr         // return from IRQ to the location of the restored process (lr already adjusted to the appropiate pc)



.data
.align 5
/* Fixed, known place to save and restore the state of a process (r0-15 + status register) */
saved_state:    .space 17 * 4
.align 5
/* Stack for the IRQ mode (4 kB) */
irq_stack:      .space 0x1000
irq_stack_top:
/* Stack for the SVC mode (4 kB) */
svc_stack:      .space 0x1000
svc_stack_top:
/* Stack for the USR mode (64 kB) */
user_stack:     .space 0x10000
user_stack_top:
