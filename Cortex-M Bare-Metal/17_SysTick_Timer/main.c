#include "TM4C123.h"                    // Device header
#include "systick.h"
#include "gpio.h"

int main ()
{
	GPIO_Init();
	SysTick_Init();
	
	while (1)
	{
		if (Timeout()) 				// Pooling over Bit-16 - COUNT to determine if the systick has hit 0.
		{
			GPIOF->DATA ^= GREEN;
		}
	}
	
}

