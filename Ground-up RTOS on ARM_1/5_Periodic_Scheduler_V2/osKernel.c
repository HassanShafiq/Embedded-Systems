//Scheduler
//TCB
//Stack for TCBs

// Implementation of the interface created in osKernel.h:
#include "osKernel.h"
#include "TM4C123.h"                    // Device header


#define		NUM_OF_THREADS		3
#define		STACK_SIZE				100
#define		BUS_FREQ					16000000
#define		SYSPRI3_R					(*((volatile	uint32_t*)0xE000ED20))

uint32_t 	MILLIS_PRESCALER;
uint32_t	periodic_tick;

// Only osKernelLaunch can launch the scheduler using osSchedulerLaunch()
void osSchedulerLaunch();
	
struct tcb{
	int32_t *stackpt;
	struct tcb *nextPt;
};

typedef	struct tcb tcbType;
tcbType tcbs[NUM_OF_THREADS];
tcbType	*currentPt;
int32_t TCB_STACK[NUM_OF_THREADS][STACK_SIZE];

void osKernelStackInit(int thread_number)
{
	tcbs[thread_number].stackpt = &TCB_STACK[thread_number][STACK_SIZE-16];			//Initializing stack pointer
	TCB_STACK[thread_number][STACK_SIZE-1] = 0x01000000;												//Setting the bit-24 of xPSR register as 1 to explicitly instruct the core for THUMB mode
}

uint8_t osKernelAddThreads( void(*task0)(void), void(*task1)(void), void(*task2)(void))
{
	// This sequence of operations needs to be exclusive/atomic. Hence interrupts should be disabled.
	__disable_irq();
	tcbs[0].nextPt = &tcbs[1];
	tcbs[1].nextPt = &tcbs[2];
	tcbs[2].nextPt = &tcbs[0];
	
	osKernelStackInit(0);
	TCB_STACK[0][STACK_SIZE-2] = (int32_t)(task0); 															// Initializing PCs in TCB stacks
	osKernelStackInit(1);
	TCB_STACK[1][STACK_SIZE-2] = (int32_t)(task1);
	osKernelStackInit(2);
	TCB_STACK[2][STACK_SIZE-2] = (int32_t)(task2);
	
	currentPt = &tcbs[0];
	__enable_irq();
	
	return 1;
}

void osKernelInit(void)
{
	__disable_irq();
	MILLIS_PRESCALER = BUS_FREQ / 1000;
}
			

void osKernelLaunch(uint32_t quanta)
{
	SysTick->CTRL		= 0x0;
	SysTick->VAL		= 0x0;
	SysTick->LOAD		= (quanta * MILLIS_PRESCALER)-1;
	SYSPRI3_R				= (SYSPRI3_R&0x00FFFFFF) | 0xE0000000;											//Set SYSTICK Priority as 7
	SysTick->CTRL		= 0x00000007;
	
	osSchedulerLaunch();																												// Only osKernelLaunch can launch the scheduler using osSchedulerLaunch()
	__enable_irq();
}

void osSchedulerRoundRobin(void)
{
	if(++periodic_tick == PERIOD)
	{
		(*Task3)(); 								// Accessing Task3 via pointer
		periodic_tick = 0;
		
	}
	currentPt = currentPt->nextPt;
}