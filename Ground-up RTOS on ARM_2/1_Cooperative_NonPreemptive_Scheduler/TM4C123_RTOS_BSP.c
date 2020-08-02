#include "TM4C123_RTOS_BSP.h"
#include "TM4C123.h"                    // Device header

#define		RED		(1U<<1)
#define		BLUE	(1U<<2)
#define		GREEN	(1U<<3)

unsigned int LED_PIN;

//-----------------Start of ADC APIs***************************//

void ADC0_Init(void)
{
  /* enable clocks */
    SYSCTL->RCGCGPIO |= 0x10;   /* enable clock to GPIOE (AIN0 is on PE3) */
    SYSCTL->RCGCADC |= 1;       /* enable clock to ADC0 */
    
    /* initialize PE3 for AIN0 input  */
    GPIOE->AFSEL |= 8;       /* enable alternate function */
    GPIOE->DEN &= ~8;        /* disable digital function */
    GPIOE->AMSEL |= 8;       /* enable analog function */
   
    /* initialize ADC0 */
    ADC0->ACTSS &= ~8;        /* disable SS3 during configuration */
    ADC0->EMUX &= ~0xF000;    /* software trigger conversion */
    ADC0->SSMUX3 = 0;         /* get input from channel 0 */
    ADC0->SSCTL3 |= 6;        /* take one sample at a time, set flag at 1st sample */
    ADC0->ACTSS |= 8;       /* enable ADC0 sequencer 3 */
}

	volatile uint32_t _result;

 uint32_t ADC0_getResult(void)
{

	 ADC0->PSSI |= 8;        /* start a conversion sequence 3 */
   while((ADC0->RIS & 8) == 0){} ;   /* wait for conversion complete */
   _result = ADC0->SSFIFO3; /* read conversion result */
   ADC0->ISC = 8;          /* clear completion flag */
	
	 return _result;
}


//-----------------End of ADC APIs***************************//


//-----------------Start of Probe APIs***************************//
void Probe_Init(void)
{
   SYSCTL->RCGCGPIO =(1U<<1);
	 GPIOB->DIR |=(CH0|CH1|CH2|CH3);
	GPIOB->DEN |=(CH0|CH1|CH2|CH3);
}

void Probe_CH0(void)
{
	GPIOB->DATA ^= CH0;
}

void Probe_CH1(void)
{
		GPIOB->DATA ^= CH1;

}
void Probe_CH2(void)
{
		GPIOB->DATA ^= CH2;

}
void Probe_CH3(void)
{
	
}
//---------------End of Probe APIs*******************************/


//*******************Start of SystemClockConfig APIs******************/
void SystemClock_Config80Mhz(void)
{

  SYSCTL->RCC2 |= SYSCTL_RCC2_USERCC2;
  SYSCTL->RCC2|= SYSCTL_RCC2_BYPASS2;

  SYSCTL->RCC &= ~SYSCTL_RCC_XTAL_M;  
	DelayMs(1);          //Very important

  SYSCTL->RCC += SYSCTL_RCC_XTAL_16MHZ;

  SYSCTL->RCC2 &= ~SYSCTL_RCC2_OSCSRC2_M;

  SYSCTL->RCC2 += SYSCTL_RCC2_OSCSRC2_MO;

  SYSCTL->RCC2 &= ~SYSCTL_RCC2_PWRDN2;
	
  SYSCTL->RCC2|= SYSCTL_RCC2_DIV400;  
  SYSCTL->RCC2 = (SYSCTL->RCC2&~0x1FC00000)  + (4<<22);      
  while((SYSCTL->RIS &SYSCTL_RIS_PLLLRIS)==0){};
  SYSCTL->RCC2 &= ~SYSCTL_RCC2_BYPASS2;
	
}
//*******************************End of SystemClockConfig APIs**************/




void DelayMs(uint32_t ttime)
{
	 	int i;

		SYSCTL->RCGCTIMER |=2;
	  TIMER1->CTL = 0;
   	TIMER1->CFG = 0x04;    //16-bits mode
	  TIMER1->TAMR = 0x02;        /* periodic mode and down-counter */
    TIMER1->TAILR = 120000 - 1; 
    TIMER1->ICR = 0x1;          /* clear the TimerA timeout flag*/
    TIMER1->CTL |= 0x01;        /* enable Timer A after initialization */
   
	   for(i = 0; i < ttime; i++)
    {
        while ((TIMER1->RIS & 0x1) == 0) ;      /* wait for TimerA timeout flag */
        TIMER1->ICR = 0x1;      /* clear the TimerA timeout flag */
    }
}


/* Setup Timer2A to create 10 Hz interrupt */
void Timer2A_Init(void)
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
			GPIOF->DATA	^= LED_PIN;
  			TIMER2->ICR = 0x1;     /* clear the Timer2A timeout flag */
        readback = TIMER2->ICR;   /* a read to force clearing of interrupt flag */
    }
    else
    {   /* should not get here, but if we do */
        TIMER2->ICR = TIMER2->MIS;  /* clear all flags */
        readback = TIMER2->ICR;      /* a read to force clearing of interrupt flag */
    }
}

void Timer3A_Init500HzInt(void){
	     volatile uint32_t delay;

                                // activate timer3
  SYSCTL->RCGCTIMER|= (1U<<3);
                                   // allow time for clock to stabilize
  delay = SYSCTL->RCGCTIMER;          // allow time to finish activating
  TIMER3->CTL =0 ; // disable timer2A during setup
  TIMER3->CFG = 0; // configure for 32-bit timer mode
  TIMER3->TAMR = 0x02;
  TIMER3->TAPR = 0;             // No Prescaler

	TIMER3->TAILR = 32000;          // start value for 500 Hz interrupts
  
	TIMER3->IMR |= 0x01;// enable timeout (rollover) interrupt
  TIMER3->ICR = 0x01;
  TIMER3->CTL|= 0x01;  
                                   // Timer3A=priority 4
	NVIC->IP[35] = 2<<5;  //set to priority level 4
	NVIC_EnableIRQ(35);
}

void TIMER3A_Handler(void)
{
    volatile int readback;
    if (TIMER3->MIS & 0x1)     /* Timer3A timeout flag */
    {            
      /*******Task****/
  			TIMER3->ICR = 0x1;     /* clear the Timer3A timeout flag */
        readback = TIMER3->ICR;   /* a read to force clearing of interrupt flag */
    }
    else
    {   /* should not get here, but if we do */
        TIMER3->ICR = TIMER3->MIS;  /* clear all flags */
        readback = TIMER3->ICR;      /* a read to force clearing of interrupt flag */
    }
}


void WTimer5_Init(void){
	
  SYSCTL->RCGCWTIMER|= 0x20;     // activate clock for Wide Timer5
  while((SYSCTL->PRWTIMER&0x20) == 0){};// allow time for clock to stabilize
  WTIMER5->CTL &= ~0x100;// disable Wide Timer5B during setup
  WTIMER5->CFG = 0x04;// configure for 32-bit timer mode
                                   // configure for periodic mode, default down-count settings
  WTIMER5->TBMR = 0x02;
  WTIMER5->TBILR= 0xFFFFFFFF;    // reload value
  WTIMER5->TBPR = 79;             // 1 MHz resolution
  WTIMER5->ICR = 0x100;// clear WTIMER5B timeout flag
  WTIMER5->IMR &= ~0x100;// disarm timeout interrupt
  WTIMER5->CTL |= 0x100; // enable Wide Timer0B 32-b
}

uint32_t getMicro(void){
  return (0xFFFFFFFF - WTIMER5->TBV);
}

void GPIOF_Init_LED(unsigned int LED)
{
	SYSCTL->RCGCGPIO	|= 0x20; //Clock gating control for PortF
	GPIOF->DIR				|= LED;
	GPIOF->DEN				|= LED;
	
	LED_PIN = LED;
}

void BSP_LED_redToggle()
{
	GPIOF->DATA	^= RED;
}

void BSP_LED_blueToggle()
{
	GPIOF->DATA	^= BLUE;
}	

void BSP_LED_greenToggle()
{
	GPIOF->DATA	^= GREEN;
}