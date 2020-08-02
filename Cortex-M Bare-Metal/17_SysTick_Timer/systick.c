#include "TM4C123.h"                    // Device header
#include "systick.h"


void SysTick_Init(void)
{
	SysTick->CTRL 		= CLEAR_R;							// Disable SysTick during configuration
	SysTick->LOAD			= ONESEC/4;							// Provide reload value as 16000000-1 as our clock source is Main Oscillator (MOSC)
	SysTick->VAL			= CLEAR_R;							// Clear the current value register
	SysTick->CTRL			= ENMOSC;								// CLK_SRC as System Clock (16MHz) and enable the SysTick in a single instruction.
}

bool Timeout(void)
{
	return (SysTick->CTRL & 0x10000);					// Checks the SysTick Timeout on Bit-16 for COUNT value
}