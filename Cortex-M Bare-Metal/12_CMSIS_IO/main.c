#include "TM4C123.h"                    // Device header
#include "gpio_functions.h"
#include "portf_initialize.h"
#include "constants.h"


//uint32_t	SW_INPUT();
//void delay (uint32_t mi);
//uint32_t LED_ON(uint32_t LED);

int main()
{
	uint32_t	sw_state;
	// Initializing PortF:
	GPIOF_Init();
	
	while(1)
	{
		sw_state = SW_INPUT();
		
		switch(sw_state){
			case	SW1_KEY:
				LED_ON(GREEN);
				break;
			case	SW2_KEY:
				LED_ON(BLUE);
				break;
		}
	}
}

