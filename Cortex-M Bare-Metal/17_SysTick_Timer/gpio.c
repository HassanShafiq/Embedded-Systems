#include "TM4C123.h"                    // Device header
#include "gpio.h"

void GPIO_Init()
{
	SYSCTL->RCGCGPIO 	|= 0x20;
	GPIOF->DIR				|= GREEN;
	GPIOF->DEN				|= GREEN;
}