#include "TM4C123.h"                    // Device header
#include "delay.h"
#include <stdint.h>

#define		RED			(1U << 1)
#define		BLUE		(1U << 2)
#define		GREEN		(1U << 3)

int main ()
{
	// Initializing Clock Gating Control for PortF:
	SYSCTL->RCGC2 = 0x00000020;
		
	// Initializing Digital Enable Register for PortF PF3-1:
	GPIOF->DEN = 0x0E;
		
	// Initialzing Direction Register for PortF PF3-1:
	GPIOF->DIR = 0x0E;
		
	while (1)
	{
		// Writing Data to PortF Data register for PF3-1:
		//GPIO_PORTF_DATA_R = (BLUE | GREEN) & ~RED;
		GPIOF->DATA = (BLUE | GREEN | RED);
		call_delay(10);
		
		// Writing Data to PortF Data register for PF3-1:
		GPIOF->DATA = ~(RED | BLUE | GREEN);
		call_delay(10);
	}
}

