#include "osKernel.h"
#include "TM4C123_RTOS_BSP.h"

#define	QUANTA	1000
#define		RED		(1U<<1)
#define		BLUE	(1U<<2)
#define		GREEN	(1U<<3)

uint32_t count0,count1,count2;

void Task0(void);
void Task1(void);
void Task2(void);

int main(void)
{
	GPIOF_Init_LED(GREEN | RED | BLUE);
	
	osKernelInit();
	osKernelAddThreads(&Task0,&Task1,&Task2);
	osKernelLaunch(QUANTA);
	
}

void Task0(void)
{
	while(1){
	 count0++;
	 osThreadYield();
	 BSP_LED_redToggle();
	 }
}

void Task1(void)
{
	while(1){
	count1++;
	//osThreadYield();
	BSP_LED_blueToggle();
	 }
}

void Task2(void)
{
	while(1){
		count2++;
		osThreadYield();
		BSP_LED_greenToggle();
	 }
}