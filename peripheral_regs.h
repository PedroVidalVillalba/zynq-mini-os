#ifndef PERIPHERAL_REGS_H
#define PERIPHERAL_REGS_H

typedef unsigned char byte;
typedef unsigned int usize;

/* GPIO Registers */
extern volatile byte* const GPIO_LEDS;
extern volatile byte* const GPIO_SWITCHES;

/* UART Registers */
extern byte* const UART_BASE;
extern volatile usize* const UART_CONTROL_REG0;
extern volatile usize* const UART_MODE_REG0;
extern volatile usize* const UART_BAUD_RATE_GEN_REG0;
extern volatile usize* const UART_BAUD_RATE_DIVIDER_REG0;
extern volatile usize* const UART_MODEM_CONTROL_REG0;
extern volatile usize* const UART_MODEM_STS_REG0;
extern volatile usize* const UART_TX_RX_FIFO0;
extern volatile usize* const UART_CHANNEL_STS_REG0;

/* Private Timer Registers */
extern byte* const PRIVATE_TIMER;           	// Private Timer Base Address
extern volatile usize* const PRIVATE_LOAD;		// Private Timer Load Register
extern volatile usize* const PRIVATE_COUNTER; 	// Private Timer Counter Register
extern volatile usize* const PRIVATE_CONTROL;	// Private Timer Control Register
extern volatile usize* const PRIVATE_STATUS;	// Private Timer Interrupt Status Register

/* GIC Distributor Registers */
extern byte* const GICD_BASE;         			// Distributor Base Address
extern volatile usize* const GICD_CTLR;    		// Distributor Control Register
extern volatile usize* const GICD_TYPER;    	// Interrupt Controller Type Register
extern volatile usize* const GICD_IIDR;    		// Distributor Implementer Identification Register
extern volatile usize* const GICD_IGROUPR;   	// Interrupt Group Registers
extern volatile usize* const GICD_ISENABLER; 	// Interrupt Set-Enable Registers
extern volatile usize* const GICD_ICENABLER;	// Interrupt Clear-Enable Registers
extern volatile usize* const GICD_ISPENDR;		// Interrupt Set-Pending Registers
extern volatile usize* const GICD_ICPENDR;		// Interrupt Clear-Pending Registers
extern volatile usize* const GICD_ISACTIVER;	// Interrupt Set-Active Registers
extern volatile usize* const GICD_ICACTIVER;	// Interrupt Clear-Active Registers
extern volatile usize* const GICD_IPRIORITYR;	// Interrupt Priority Registers
extern volatile usize* const GICD_ITARGETSR;	// Interrupt Processor Targets Registers
extern volatile usize* const GICD_ICFGR;		// Interrupt Configuration Registers
extern volatile usize* const GICD_NSACR;		// Non-secure Access Control Registers
extern volatile usize* const GICD_SGIR;  		// Software Generated Interrupt Register
extern volatile usize* const GICD_CPENDSGIR;	// SGI Clear-Pending Registers
extern volatile usize* const GICD_SPENDSGIR;	// SGI Set-Pending Registers
extern volatile usize* const GICD_ICPIDR;  		// Peripheral ID0-ID7 Registers
extern volatile usize* const GICD_ICCIDR;		// Component ID0-ID4 Registers

/* GIC CPU Interface Registers */
extern byte* const GICC_BASE;					// CPU Interface Base Address
extern volatile usize* const GICC_CTLR;			// CPU Interface Control Register
extern volatile usize* const GICC_PMR; 			// Interrupt Priority Mask Register
extern volatile usize* const GICC_BPR; 			// Binary Point Register
extern volatile usize* const GICC_IAR;			// Interrupt Acknowledge Register
extern volatile usize* const GICC_EOIR;			// End of Interrupt Register
extern volatile usize* const GICC_RPR;			// Running Priority Register
extern volatile usize* const GICC_HPPIR;		// Highest Priority Pending Interrupt Register
extern volatile usize* const GICC_ABPR;			// Aliased Binary Point Register
extern volatile usize* const GICC_AIAR;			// Aliased Interrupt Acknowledge Register
extern volatile usize* const GICC_AEOIR;		// Aliased End of Interrupt Register
extern volatile usize* const GICC_AHPPIR;		// Aliased Highest Priority Pending Interrupt Register
extern volatile usize* const GICC_APR; 			// Active Priorities Registers
extern volatile usize* const GICC_NSAPR; 		// Non-secure Active Priorities Registers
extern volatile usize* const GICC_IIDR;			// CPU Interface Identification Register


#endif // PERIPHERAL_REGS_H
