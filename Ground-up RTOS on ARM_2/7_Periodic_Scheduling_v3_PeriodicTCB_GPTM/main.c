
#include "osKernel.h"
#include "TM4C123_RTOS_BSP.h"


#define	QUANTA	10
#define		RED		(1U<<1)
#define		BLUE	(1U<<2)
#define		GREEN	(1U<<3)

uint32_t count0,count1,count2, pcount0, pcount1;

void Task0(void)
{
	 while(1){
	 count0++;
	 //BSP_LED_greenToggle();
		 
	 }
}

void Task1(void)
{
	 while(1){
	 count1++;
	 //BSP_LED_blueToggle();

	 }
}

void Task2(void)
{
	 while(1){
	  count2++;
		 //BSP_LED_redToggle();

	 }
}

void periodicTask_1(void)
{
	pcount0++;
	BSP_LED_redToggle();
}

void periodicTask_2(void)
{
	pcount1++;
	BSP_LED_blueToggle();
}

int main(void)
{
	GPIOF_Init_LED(GREEN | RED | BLUE);
	//Timer2A_Init();
	
	osKernelInit();
	osKernelAddThreads(&Task0,&Task1,&Task2);
	// Periodic Task 1 configured at 100ms and Periodic Task 2 configured at 1000ms:
	osKermelAddPeriodicThreads(&periodicTask_1, 100, &periodicTask_2, 1000);
	osKernelLaunch(QUANTA);
	
}