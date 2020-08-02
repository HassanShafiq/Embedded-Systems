#include "TM4C123.h"                    // Device header

void Timer2A_RisingEdgeEvent_Init(void);
int Timer2A_RisingEdgeEvent_Capture(void);
uint32_t	number_of_events	= 0;

int main(void)
{
	Timer2A_RisingEdgeEvent_Init();
	while(1)
	{
		number_of_events	= Timer2A_RisingEdgeEvent_Capture();
	}
}

void Timer2A_RisingEdgeEvent_Init(void)
{
	SYSCTL->RCGCTIMER |= 	0x04;
	SYSCTL->RCGCGPIO	|= 	0x20;
	GPIOF->DIR				&=	~0x10;
	GPIOF->PUR				= 	0x10;
	GPIOF->DEN				|=	0x10;
	GPIOF->AFSEL			|=	0x10;
	GPIOF->PCTL				&=	~0x000F0000;
	GPIOF->PCTL				|=	0x00070000;
	
	TIMER2->CTL				=		0x00;
	TIMER2->CFG				= 	0x04;
	TIMER2->TAMR			=		0x013;
	TIMER2->TAMATCHR	= 	0xFFFF;
	TIMER2->TAPMR			=		0xFF;
	TIMER2->CTL				|=	0x01;
}

int Timer2A_RisingEdgeEvent_Capture(void)
{
	return	TIMER2->TAR;
}