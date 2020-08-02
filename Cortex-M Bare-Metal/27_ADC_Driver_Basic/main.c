#include "TM4C123.h"                    // Device header

// SS = Sample Sequencer
// SS0 - 8 Samples
// SS1 - 4 Samples
// SS2 - 4 Samples
// SS3 - 1 Samples

// Options to start ADC conversion using:
// Timers
// PWM
// Analog Comparator
// Externel Signal from GPIO
// Software Trigger

// ADCACTSS
// ADCEMUX
// ADCPSSI
// ADCRIS		>> To detect the end-of-conversion, by polling a particular bit flag in this register and then we can read the value of ADC from the sample sequencer\
//							or we can use an interrupt instead.							

int result = 0;

int main(void)
{
	SYSCTL->RCGCGPIO	|=	0x10;		// Enable Run Mode clock for PORTE
	SYSCTL->RCGCADC		|= 	0x01;		// Enable Run Mode clock for ADC Module 0
		
	// initialize PE3 for analog input:
	GPIOE->AFSEL			|=	0x08;		// Enable alternate funtion
	GPIOE->DEN				&= 	~0x08;	// Disable digital function
	GPIOE->AMSEL			|=	0x08;		// Enable analog function
	
	// initializing ADC_0:
	ADC0->ACTSS				&=	~0x08;	// Disable Sample Sequencer 3 (SS3)
	ADC0->EMUX				&=	~0xF000;// Software Trigger conversion option
	ADC0->SSMUX3			= 	0x00;		// Get input from channel 0
	ADC0->SSCTL3			|=	0x06;		// Take one sample at a time, set flat at 1st sample
	ADC0->ACTSS				|= 	0x08; 	// Enable SS3
	
	while(1)
	{
		ADC0->PSSI			|= 	0x08;		// Start a conversion at SS3
		while((ADC0->RIS	&	0x08) == 0){}
		result = ADC0->SSFIFO3;
		ADC0->ISC				= 	0x08;		// Clearing the completion flag
	}
}

