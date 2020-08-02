#include "TM4C123.h"                    // Device header


//Author : cortex-m.com
//Tiltle :Interfacing HC-SR04 Ultrasonic sensor with Tiva C ARM Cortex-M4
#include &quot;TM4C123.h&quot;                    // Device header
#include &lt;stdint.h&gt;
 
void delay_Microsecond(uint32_t time);
void Timer0_init(void);
uint32_t measureD(void);
 
const double _16MHz_1clock = 62.5e-9; /*Value of 1clock cycle in nanoseconds*/
const uint32_t MULTIPLIER  = 5882;  /*Derived from speed of sound*/
 
#define ECHO (1U&lt;&lt;6) //PB6
#define TRIGGER(1U&lt;&lt;4) //PA4(OUTPUT)
#define BLUE_LED (1U&lt;&lt;2)//PF3 onboard Blue LED 
uint32_t highEdge,lowEdge;
uint32_t ddistance; /*Distance in centimeters*/
uint32_t counter =0; 
uint32_t measureD(void) { 
GPIOA-&gt;DATA &amp;=~TRIGGER;
    delay_Microsecond(12);
    GPIOA-&gt;DATA |= TRIGGER;
    delay_Microsecond(12);
    GPIOA-&gt;DATA &amp;=~TRIGGER;
    /*Capture firstEgde i.e. rising edge*/
    TIMER0-&gt;ICR =4;
    while((TIMER0-&gt;RIS &amp; 4)==0){}; //Wait till captured
        highEdge =  TIMER0-&gt;TAR;
 
        /*Capture secondEdge i.e. falling edge */
        TIMER0-&gt;ICR =4; //clear timer capture flag
        while((TIMER0-&gt;RIS &amp; 4)  ==0){};
            lowEdge = TIMER0-&amp;gt;TAR;
              ddistance = lowEdge -highEdge;
              ddistance = _16MHz_1clock *(double) MULTIPLIER *(double)ddistance;
 
            return ddistance;
 
}
int main(void){
    SYSCTL-&gt;RCGCGPIO |=(1U&lt;&lt;0); //Enable clock for PORTA 
        SYSCTL-&gt;RCGCGPIO |=(1U&lt;&lt;5); //Enable clock for PORTF 
        GPIOA-&gt;DIR =TRIGGER;  
    GPIOF-&gt;DIR =BLUE_LED;
    GPIOA-&gt;DEN |=(ECHO)|(TRIGGER);
    GPIOF-&gt;DEN |= BLUE_LED;
 
    while(1){
        Timer0_init();
         measureD();
    if(measureD() &lt; 15) 
   GPIOF-&gt;DATA |=BLUE_LED;
   else
   GPIOF-&gt;DATA &amp;=~BLUE_LED;
   delay_Microsecond(100);
 
  }
}
void delay_Microsecond(uint32_t time)
{
    int i;
    SYSCTL-&gt;RCGCTIMER |=(1U&lt;&lt;1); 
        TIMER1-&gt;CTL=0;
    TIMER1-&gt;CFG=0x04;
    TIMER1-&gt;TAMR=0x02;
    TIMER1-&gt;TAILR= 16-1;
    TIMER1-&gt;ICR =0x1;
    TIMER1-&gt;CTL |=0x01;
 
    for(i=0;i&lt;time;i++){ 
       while((TIMER1-&gt;RIS &amp; 0x1)==0);
        TIMER1-&gt;ICR = 0x1;
    }
 
}
void Timer0_init(void)
{
    SYSCTL-&gt;RCGCTIMER |=(1U&lt;&lt;0); 
        SYSCTL-&gt;RCGCGPIO |=(1U&lt;&lt;1); 
        GPIOB-&gt;DIR &amp;=~ECHO;
    GPIOB-&gt;DEN |=ECHO;
    GPIOB-&gt;AFSEL |=ECHO;
    GPIOB-&gt;PCTL &amp;=~0x0F000000;
    GPIOB-&gt;PCTL |= 0x07000000;
 
    TIMER0-&gt;CTL &amp;=~1;
    TIMER0-&gt;CFG =4;
    TIMER0-&gt;TAMR = 0x17;
    TIMER0-&gt;CTL |=0x0C;
    TIMER0-&gt;CTL |=1;
}