#include "TM4C123.h"                    // Device header
#include "osKernel.h"

#define		QUANTA	10

uint32_t	count1, count2, count3;

void Task0(void);
void Task1(void);
void Task2(void);

int main (void)
{
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


