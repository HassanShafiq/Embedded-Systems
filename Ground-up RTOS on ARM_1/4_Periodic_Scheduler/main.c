#include "TM4C123.h"                    // Device header
#include "osKernel.h"
#include "TM4C123_RTOS_BSP.h"

#define		QUANTA	1
#define		RED		(1U<<1)
#define		BLUE	(1U<<2)
#define		GREEN	(1U<<3)

uint32_t	count1, count2, count3;

void Task0(void);
void Task1(void);
void Task2(void);

int main (void)
{
	GPIOF_Init_LED(GREEN | RED | BLUE);
	Timer2A_Init();
	
	while(1)
	{
		osKernelInit();
		osKernelAddThreads(&Task0, &Task1, &Task2);
		osKernelLaunch(QUANTA);
		
	}
}

void Task0(void)
{
	while(1)
	{
		count1++;
	}
}

void Task1(void)
{
	while(1)
	{
		count2++;
	}
}

void Task2(void)
{
	while(1)
	{
		count3++;
	}
}


