#include "constants.h"
#include "gpio_functions.h"
#include "TM4C123.h"                    // Device header

uint32_t	SW_INPUT()
{
	return GPIOF->DATA & 0x11;
}

uint32_t LED_ON(uint32_t LED)
{
	GPIOF->DATA = LED;
	delay(500);
	GPIOF->DATA &= ~LED;
	delay(500);
}

void delay (uint32_t milliseconds)
{
	int	volatile	delay = 0;
	while (delay < milliseconds)
	{
	//milli-second delay:
		for (int i = 0; i < 4000 ; i++)
		{
			// Do nothing
		}
		delay++;
	}
}
