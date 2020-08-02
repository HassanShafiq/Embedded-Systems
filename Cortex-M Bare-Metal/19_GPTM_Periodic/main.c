#include "TM4C123.h"                    // Device header

#define		RED		(1U<<1)
#define		BLUE	(1U<<2)
#define		GREEN	(1U<<3)

void Timer_1_Periodic(int milli_seconds);

int main(void)
{
	unsigned int delay = 500;
	SYSCTL->RCGCGPIO	|= 0x20; //Clock gating control for PortF
	GPIOF->DIR				|= BLUE;
	GPIOF->DEN				|= BLUE;
	
	while(1)
	{
		GPIOF->DATA	^= BLUE;
		Timer_1_Periodic(2000);	
	}
}

void Timer_1_Periodic(int milli_seconds)
{
	SYSCTL->RCGCTIMER	|= 0x01; 		//Clock gating control for Timer 0.
	TIMER0->CTL		|= 0x00; 				//Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making any changes.
	TIMER0->CFG		= 0x04;					//Write the GPTM Configuration Register (GPTMCFG) with a value of 0x04, for 16-bit timer.
	TIMER0->TAMR	= 0x02;					//Write a value of 0x1 for One-Shot mode.
	TIMER0->TAILR = (16000 - 1);	//Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
	TIMER0->ICR		= 0x01;					//Clearing GPTM Timer A Time-Out Raw Interrupt so as to enable re-countdown.
	TIMER0->CTL		|= 0x01;				//Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
	
	for (int j = 0 ; j < milli_seconds ; j++)
	{
		while((TIMER0->RIS	& 0x01) == 0);	//Wait for timeout flag to be set when the timer hits 0.
		TIMER0->ICR = 0x01;									//Clearing GPTM Timer A Time-Out Raw Interrupt so as to enable re-countdown, once again.
	}
}
