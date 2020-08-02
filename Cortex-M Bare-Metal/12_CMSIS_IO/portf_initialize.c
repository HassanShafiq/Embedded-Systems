#include "TM4C123.h"                    // Device header
#include "constants.h"


#define		UNLOCK_KEY		0x4C4F434B
void GPIOF_Init()
{
	SYSCTL->RCGCGPIO |= (1U<<5);
	GPIOF->LOCK = UNLOCK_KEY;
	GPIOF->CR = 0xFF;
	GPIOF->DIR |= (RED | BLUE | GREEN);
	GPIOF->PUR |= (SW1 | SW2);
	GPIOF->DEN |= (RED | BLUE | GREEN | SW1 | SW2);
}
