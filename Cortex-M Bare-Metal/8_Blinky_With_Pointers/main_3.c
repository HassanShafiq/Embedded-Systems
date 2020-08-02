#include "tm4c123gh6pm.h"
#include "delay.h"
#include <stdint.h>

#define		RED			(1U << 1)
#define		BLUE		(1U << 2)
#define		GREEN		(1U << 3)

int main ()
{
	// Initializing Clock Gating Control for PortF:
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;
		
	// Initializing Digital Enable Register for PortF PF3-1:
	GPIO_PORTF_DEN_R = 0x0E;
		
	// Initialzing Direction Register for PortF PF3-1:
	GPIO_PORTF_DIR_R = 0x0E;
		
	while (1)
	{
		// Writing Data to PortF Data register for PF3-1:
		//GPIO_PORTF_DATA_R = (BLUE | GREEN) & ~RED;
		GPIO_PORTF_DATA_R = (BLUE | GREEN | RED);
		call_delay(10);
		
		// Writing Data to PortF Data register for PF3-1:
		GPIO_PORTF_DATA_R = ~(RED | BLUE | GREEN);
		call_delay(10);
	}
}

