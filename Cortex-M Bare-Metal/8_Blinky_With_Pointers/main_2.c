//Blue-Blinky 
//main.c
//Author : Israel Gbati (cortex-m.com)
//Runs on TM4C123 

/*

#include "tm4c123gh6pm.h"
#include <stdint.h>

volatile int counter = 0;
void delay(void);
int main(){
  SYSCTL_RCGCGPIO_R = 0x20;
	GPIO_PORTF_DIR_R = 0x04;
	GPIO_PORTF_DEN_R = 0x04;
	
	while(1){
		GPIO_PORTF_DATA_R =0x04;
		counter =0;
	  delay();
		counter =0;
		GPIO_PORTF_DATA_R =0x00;
		delay();
		}
}

 void delay(void){
  while(counter<1000000){
		 counter++;
		}
 } */