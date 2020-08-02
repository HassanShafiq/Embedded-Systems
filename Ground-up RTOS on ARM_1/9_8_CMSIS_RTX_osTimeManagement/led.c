#include "TM4C123.h"                    // Device header

#define		RED			(1U<<1)
#define		GREEN		(1U<<2)
#define		BLUE		(1U<<3)

void	LEDs_Init(void);
void	toggle_RED(void);
void	toggle_BLUE(void);
void	toggle_GREEN(void);

void	LEDs_Init(void)
{
	SYSCTL->RCGCGPIO	= 0x20;
	GPIOF->DIR				= 0x0E;
	GPIOF->DEN				= 0x0E;
	//GPIOF->DATA				= 0x0E;
}
	
void	toggle_RED(void)
{
	GPIOF->DATA		^= RED;
}
	
void	toggle_BLUE(void)
{
	GPIOF->DATA		^= BLUE;
}
	
void	toggle_GREEN(void)
{
	GPIOF->DATA		^= GREEN;
}