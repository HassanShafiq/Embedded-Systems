#include "TM4C123.h"                    // Device header

#define		RED		(1U<<1)
#define		BLUE	(1U<<2)
#define		GREEN	(1U<<3)

void Timer_1_Periodic_Interrupt(void);

int main(void)
{
	unsigned int delay = 500;
	SYSCTL->RCGCGPIO	|= 0x20; //Clock gating control for PortF
	GPIOF->DIR				|= GREEN;
	GPIOF->DEN				|= GREEN;
	Timer_1_Periodic_Interrupt();
	
	while(1)
	{
		
	}
}

void Timer_1_Periodic_Interrupt(void)
{
	SYSCTL->RCGCTIMER |= 4;     /* enable clock to Timer Block 2   */
    TIMER2->CTL = 0;            /* disable Timer2 before initialization */
    TIMER2->CFG = 0x04;         /* 16-bit option */
    TIMER2->TAMR = 0x02;        /* periodic mode and down-counter */
    TIMER2->TAPR = 250;         /* 16000000 Hz / 250 = 64000 Hz */
    TIMER2->TAILR = 6400;       /* 64000 Hz / 6400 = 10 Hz */
    TIMER2->ICR = 0x1;          /* clear the Timer2A timeout flag */
    TIMER2->IMR |= 0x01;        /* enable Timer2A timeout interrupt */
    TIMER2->CTL |= 0x01;        /* enable Timer2A after initialization */
    NVIC->ISER[0] |= 0x00800000;  /* enable IRQ23 (D23 of ISER[0]) */
}


void TIMER2A_Handler(void)
{
    volatile int readback;
    if (TIMER2->MIS & 0x1)     /* Timer2A timeout flag */
    {            
      /*******Task****/
			GPIOF->DATA	^= GREEN;
  			TIMER2->ICR = 0x1;     /* clear the Timer2A timeout flag */
        readback = TIMER2->ICR;   /* a read to force clearing of interrupt flag */
    }
    else
    {   /* should not get here, but if we do */
        TIMER2->ICR = TIMER2->MIS;  /* clear all flags */
        readback = TIMER2->ICR;      /* a read to force clearing of interrupt flag */
    }
}