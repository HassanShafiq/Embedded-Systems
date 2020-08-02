#include "TM4C123.h"                    // Device header


int main()
{
	// Configuring GPIOF for PF1-3 as LED Outputs:
	SYSCTL->RCGCGPIO	|=	0x20;
	GPIOF->DIR				|= 	0x0E;
	GPIOF->DEN				|=	0x0E;
	
	// Configuring SysTick with interrupts enabled:
	// Prior enabling/configuring an interrupt, always disable global interrupts
	// For this, we'll use the ARM Compiler Intrinsic: __disable_irq()
	__disable_irq();
	
	SysTick->LOAD			=		16000000-1;
	SysTick->CTRL			=		0x07;
	
	// Enabling global interrupts back, using ARM Compiler Intrinsic: __enable_irq():
	__enable_irq();
	
	while(1){
	
	}
}

void SysTick_Handler()
{
	GPIOF->DATA		^=		0x0E;
}