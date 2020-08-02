#include "TM4C123.h"                    // Device header

void delayMS(int delay);
	
int main(void)
{
	SYSCTL->RCGCGPIO	|=	0x20;
	GPIOF->LOCK				=		0x4C4F434B;
	GPIOF->CR					=		0x01;
	GPIOF->LOCK				=		0;

	GPIOF->DIR				&=	~0x11;
	GPIOF->DIR				|=	0x0E;
	GPIOF->DEN				|=	0x1F;
	GPIOF->PUR				|=	0x11;
	
	__disable_irq();
	
	GPIOF->IS					&=	~0x11;					//Configuring PF4, PF0 for falling-edge interrupt trigger; edge-sensitive: Register 3: GPIO Interrupt Sense (GPIOIS), offset 0x404
	GPIOF->IBE				&=	~0x11;
	GPIOF->IEV				&=	~0x11;					//falling-edge detection: Register 5: GPIO Interrupt Event (GPIOIEV), offset 0x40C
	GPIOF->ICR				|=	0x11;						//clearing any prior interrupts: Register 9: GPIO Interrupt Clear (GPIOICR), offset 0x41C
	GPIOF->IM					|=	0x11;						//unmask interrupts
	
	//Enable interrupt in NVIC and set priority:
	NVIC->IP[30]				=	 	3<<5;						//setting interrupt priority 3, refer to page 152 for PRIn regsiter
	NVIC->ISER[0]				=		0x40000000;			//enable IRQ30: Register 4: Interrupt 0-31 Set Enable (EN0), offset 0x100
	__enable_irq();
	
	while (1)
	{
		GPIOF->DATA			|=	0x02;
		delayMS(500);
		GPIOF->DATA			&=	~0x02;
		delayMS(500);
	}
}

void GPIOF_Handler(void)
{
	volatile	int readback;
	GPIOF->DATA			&=	~0x02;
	//Toggling GREEN LED 3 times, whenever the interrupt occurs:
	for(int i = 0; i < 10 ; i++)
	{
		GPIOF->DATA			|=	0x08;
		delayMS(500);
		GPIOF->DATA			&=	~0x08;
		delayMS(500);
	}
	
	//Clearing interrupt flag before returning from the handler:
	GPIOF->ICR				|=	0x11;
	readback					= 	GPIOF->ICR;
}

void delayMS(int delay)
{
	for(int i = 0; i < delay; i++)
	{
		for(int j = 0; j < 4000 ; j++)
		{
		}
	}
}