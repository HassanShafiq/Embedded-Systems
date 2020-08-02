#include	"led.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX


void thread_RED(void const *argument);
void thread_BLUE(void const *argument);
void thread_GREEN(void const *argument);

osThreadDef(thread_RED, osPriorityNormal, 1, 0);
osThreadDef(thread_BLUE, osPriorityNormal, 1, 0);
osThreadDef(thread_GREEN, osPriorityNormal, 1, 0);

int32_t		count_1, count_2, count_3;

int main(void)
{
	LEDs_Init();
	osThreadCreate(osThread(thread_RED), NULL);
	osThreadCreate(osThread(thread_BLUE), NULL);
	osThreadCreate(osThread(thread_GREEN), NULL);
	
	while(1)
	{
		
	}
}

void thread_RED(void const *argument)
{
	while(1)
	{
		toggle_RED();
		osDelay(5000);
	}
}

void thread_BLUE(void const *argument)
{
	while(1)
	{
		toggle_BLUE();
		osDelay(5000);
	}
}

void thread_GREEN(void const *argument)
{
	while(1)
	{
		toggle_GREEN();
		osDelay(5000);
	}
}
