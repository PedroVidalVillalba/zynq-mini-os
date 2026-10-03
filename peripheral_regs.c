typedef unsigned char byte;
typedef unsigned int usize;

/* GPIO Registers */
volatile byte* const GPIO_LEDS =		(byte*) 0x41200000;
volatile byte* const GPIO_SWITCHES =	(byte*) 0x41210000;

/* UART Registers */
byte* const UART_BASE = 							(byte*) 0xE0001000;
volatile usize* const UART_CONTROL_REG0 = 			(usize*) (UART_BASE);
volatile usize* const UART_MODE_REG0 = 				(usize*) (UART_BASE + 0x00000004);
volatile usize* const UART_BAUD_RATE_GEN_REG0 = 	(usize*) (UART_BASE + 0x00000018);
volatile usize* const UART_BAUD_RATE_DIVIDER_REG0 =	(usize*) (UART_BASE + 0x00000034);
volatile usize* const UART_MODEM_CONTROL_REG0 = 	(usize*) (UART_BASE + 0x00000024);
volatile usize* const UART_MODEM_STS_REG0 = 		(usize*) (UART_BASE + 0x00000028);
volatile usize* const UART_TX_RX_FIFO0 = 			(usize*) (UART_BASE + 0x00000030);
volatile usize* const UART_CHANNEL_STS_REG0 = 		(usize*) (UART_BASE + 0x0000002C);


/* Private Timer Registers */
byte* const PRIVATE_TIMER =				(byte*) 0xF8F00600;           	// Private Timer Base Address
volatile usize* const PRIVATE_LOAD =    (usize*) (PRIVATE_TIMER + 0x0);	// Private Timer Load Register
volatile usize* const PRIVATE_COUNTER =	(usize*) (PRIVATE_TIMER + 0x4); // Private Timer Counter Register
volatile usize* const PRIVATE_CONTROL =	(usize*) (PRIVATE_TIMER + 0x8);	// Private Timer Control Register
volatile usize* const PRIVATE_STATUS =	(usize*) (PRIVATE_TIMER + 0xC);	// Private Timer Interrupt Status Register

/* GIC Distributor Registers */
byte* const GICD_BASE =	      			(byte*) 0xF8F01000;         	// Distributor Base Address
volatile usize* const GICD_CTLR =      	(usize*) (GICD_BASE + 0x0);    	// Distributor Control Register
volatile usize* const GICD_TYPER =	 	(usize*) (GICD_BASE + 0x4);    	// Interrupt Controller Type Register
volatile usize* const GICD_IIDR =	 	(usize*) (GICD_BASE + 0x8);    	// Distributor Implementer Identification Register
volatile usize* const GICD_IGROUPR =	(usize*) (GICD_BASE + 0x80);  	// Interrupt Group Registers
volatile usize* const GICD_ISENABLER =	(usize*) (GICD_BASE + 0x100);  	// Interrupt Set-Enable Registers
volatile usize* const GICD_ICENABLER = 	(usize*) (GICD_BASE + 0x180);	// Interrupt Clear-Enable Registers
volatile usize* const GICD_ISPENDR = 	(usize*) (GICD_BASE + 0x200);	// Interrupt Set-Pending Registers
volatile usize* const GICD_ICPENDR = 	(usize*) (GICD_BASE + 0x280);	// Interrupt Clear-Pending Registers
volatile usize* const GICD_ISACTIVER = 	(usize*) (GICD_BASE + 0x300);	// Interrupt Set-Active Registers
volatile usize* const GICD_ICACTIVER = 	(usize*) (GICD_BASE + 0x380);	// Interrupt Clear-Active Registers
volatile usize* const GICD_IPRIORITYR =	(usize*) (GICD_BASE + 0x400);	// Interrupt Priority Registers
volatile usize* const GICD_ITARGETSR = 	(usize*) (GICD_BASE + 0x800);	// Interrupt Processor Targets Registers
volatile usize* const GICD_ICFGR = 		(usize*) (GICD_BASE + 0xC00);	// Interrupt Configuration Registers
volatile usize* const GICD_NSACR = 		(usize*) (GICD_BASE + 0xE00);	// Non-secure Access Control Registers
volatile usize* const GICD_SGIR	= 	   	(usize*) (GICD_BASE + 0xF00);  	// Software Generated Interrupt Register
volatile usize* const GICD_CPENDSGIR = 	(usize*) (GICD_BASE + 0xF10);	// SGI Clear-Pending Registers
volatile usize* const GICD_SPENDSGIR = 	(usize*) (GICD_BASE + 0xF20);	// SGI Set-Pending Registers
volatile usize* const GICD_ICPIDR =		(usize*) (GICD_BASE + 0xFE0); 	// Peripheral ID0-ID7 Registers
volatile usize* const GICD_ICCIDR =  	(usize*) (GICD_BASE + 0xFF0);	// Component ID0-ID4 Registers

/* GIC CPU Interface Registers */
byte* const GICC_BASE = 				(byte*) 0xF8F00100;				// CPU Interface Base Address
volatile usize* const GICC_CTLR  = 		(usize*) (GICC_BASE + 0x00);	// CPU Interface Control Register
volatile usize* const GICC_PMR = 		(usize*) (GICC_BASE + 0x04); 	// Interrupt Priority Mask Register
volatile usize* const GICC_BPR = 		(usize*) (GICC_BASE + 0x08); 	// Binary Point Register
volatile usize* const GICC_IAR = 		(usize*) (GICC_BASE + 0x0C);	// Interrupt Acknowledge Register
volatile usize* const GICC_EOIR = 		(usize*) (GICC_BASE + 0x10);	// End of Interrupt Register
volatile usize* const GICC_RPR = 		(usize*) (GICC_BASE + 0x14);	// Running Priority Register
volatile usize* const GICC_HPPIR = 		(usize*) (GICC_BASE + 0x18);	// Highest Priority Pending Interrupt Register
volatile usize* const GICC_ABPR = 		(usize*) (GICC_BASE + 0x1C);	// Aliased Binary Point Register
volatile usize* const GICC_AIAR = 		(usize*) (GICC_BASE + 0x20);	// Aliased Interrupt Acknowledge Register
volatile usize* const GICC_AEOIR = 		(usize*) (GICC_BASE + 0x24);	// Aliased End of Interrupt Register
volatile usize* const GICC_AHPPIR = 	(usize*) (GICC_BASE + 0x28);	// Aliased Highest Priority Pending Interrupt Register
volatile usize* const GICC_APR = 		(usize*) (GICC_BASE + 0xD0); 	// Active Priorities Registers
volatile usize* const GICC_NSAPR = 		(usize*) (GICC_BASE + 0xE0); 	// Non-secure Active Priorities Registers
volatile usize* const GICC_IIDR = 		(usize*) (GICC_BASE + 0xFC);	// CPU Interface Identification Register

