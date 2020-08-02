#include "TM4C123.h"                    // Device header

#define		BLUE		(1U<<2)

void Wide_Timer1A_DelaySec(int seconds);

int main()
{
	SYSCTL->RCGCGPIO	|=	(1U<<5);
	GPIOF->DIR				= BLUE;
	GPIOF->DEN				= BLUE;
	
	while(1)
	{
		GPIOF->DATA ^= BLUE;
		Wide_Timer1A_DelaySec(10);
	}
}

void Wide_Timer1A_DelaySec(int seconds)
{
	SYSCTL->RCGCWTIMER	|=	0x02;				//Enable Clock to Wide Timer Module 1
	WTIMER1->CTL				=0;							//Disable Wide Timer before Initialization
	WTIMER1->CFG				= 0x04;					//32-bit option
	WTIMER1->TAMR				=	0x02;					//Periodic mode and down-counter
	WTIMER1->TAILR			=	16000000-1;		
	WTIMER1->ICR				=	0x01;
	WTIMER1->CTL				=	0x01;					//Enable Wide Timer A after Initialization
	
	for(int i = 0 ; i < seconds ; i++)
	{
		while((WTIMER1->RIS	&	0x01) == 0);
		WTIMER1->ICR	= 0x01;
	}
}