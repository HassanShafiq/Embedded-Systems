#include "TM4C123.h"                    // Device header
#include "osKernel.h"
#include "TM4C123_RTOS_BSP.h"

#define		QUANTA	10

uint32_t	count1, count2, count3;
int32_t		semaphore_1, semaphore_2;

void Task0(void);
void Task1(void);
void Task2(void);

int main (void)
{
	while(1)
	{
		osSemaphoreInit(&semaphore_1, 1);
		osSemaphoreInit(&semaphore_2, 0);
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
		osThreadYield();
	}
}

void Task1(void)
{
	while(1)
	{
		count2++;
		osThreadYield();
	}
}

void Task2(void)
{
	while(1)
	{
		count3++;
		osThreadYield();
	}
}


