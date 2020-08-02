#include "TM4C123.h"                    // Device header
#include "osKernel.h"

#define		QUANTA	1

uint32_t	count1, count2, count3;

void Task0(void);
void Task1(void);
void Task2(void);
void Task3(void);

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

// Main threads requires infinite loop and runs infinitely; while(1){}
// Periodic Threads have to execute and then exit the thread, performing a very short and bounded-task and not to execute infinitely, indefinitely.
// They have to execute when they have to execute (their period), on their own and not to require for the scheduler to kick-in to execute them.
void Task3(void)
{
	
}
