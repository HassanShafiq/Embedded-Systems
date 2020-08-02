#include "TM4C123.h"                    // Device header
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX

void thread_1(void const *argument);
void thread_2(void const *argument);
void thread_3(void const *argument);

osThreadDef(thread_1, osPriorityNormal, 1, 0);
osThreadDef(thread_2, osPriorityNormal, 1, 0);
osThreadDef(thread_3, osPriorityNormal, 1, 0);

int32_t		count_1, count_2, count_3;

int main(void)
{
	osThreadCreate(osThread(thread_1), NULL);
	osThreadCreate(osThread(thread_2), NULL);
	osThreadCreate(osThread(thread_3), NULL);
	
	while(1)
	{
		
	}
}

void thread_1(void const *argument)
{
	while(1)
	{
		++count_1;
	}
}

void thread_2(void const *argument)
{
	while(1)
	{
		++count_2;
	}
}

void thread_3(void const *argument)
{
	while(1)
	{
		++count_3;
	}
}
