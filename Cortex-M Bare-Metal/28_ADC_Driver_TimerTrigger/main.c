#include "TM4C123.h"                    // Device header
#include<stdlib.h>

// Timer based trigger of ADC0_PE3 using SS3 using Timer0 (in wide mode)

volatile int cpu_temperature = 0;

int main(void)
{
	SYSCTL->RCGCADC		|= 	0x01;		// Enable Run Mode clock for ADC Module 0
	SYSCTL->RCGCWTIMER |=	0x01;		// Enable Run Mode clock for Timer Module (wide mode)

	// Initializing ADC_0:
	ADC0->ACTSS				&=	~0x08;	// Disable Sample Sequencer 3 (SS3)
	ADC0->EMUX				&=	~0xF000;// Software Trigger conversion option
	ADC0->EMUX				|=	0x5000;// Timer Trigger based Conversion
	ADC0->SSMUX3			= 	0x00;		// Get input from channel 0
	ADC0->SSCTL3			=	0x0E;		// Take MCU temperature, set flat at 1st sample
	ADC0->ACTSS				|= 	0x08; 	// Enable SS3
	
	// Initializing Wide Timer0:
	WTIMER0->CTL			=		0x00;
	WTIMER0->CFG			=		0x04;		// 32-bit option
	WTIMER0->TAMR			=		0x02;		// Periodic mode and down-counter mode
	WTIMER0->TAILR		= 	16000000;	// Timer reload value
	WTIMER0->CTL			|=	0x20;
	WTIMER0->CTL			|=	0x01;
	
	while(1)
	{
		//ADC0->PSSI			|= 	0x08;		// Start a conversion at SS3
		while((ADC0->RIS	&	0x08) == 0){}
		cpu_temperature = 147 - (247 * ADC0->SSFIFO3) / 4096; // 12-bit resolution = 4096
		ADC0->ISC				= 	0x08;		// Clearing the completion flag
	}
}

