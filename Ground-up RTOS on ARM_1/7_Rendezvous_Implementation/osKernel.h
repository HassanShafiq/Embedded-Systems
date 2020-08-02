#ifndef _OS_KERNEL_H
#define	_OS_KERNEL_H

#include <stdint.h>
void osKernelLaunch(uint32_t quanta);
void osKernelInit(void);
void osThreadYield(void);

// SpinLock Semaphore Implementation:
void osSemaphoreInit(int32_t *semaphore, int32_t value);
void osSignalSet(int32_t *semaphore);
void osSignalWait(int32_t *semaphore);
	
uint8_t osKernelAddThreads( void(*task0)(void),
														void(*task1)(void),
														void(*task2)(void));

#endif
