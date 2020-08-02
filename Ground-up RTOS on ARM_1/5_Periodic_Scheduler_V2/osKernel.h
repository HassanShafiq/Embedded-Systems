#ifndef _OS_KERNEL_H
#define	_OS_KERNEL_H

#include <stdint.h>

#define		PERIOD	100

void osKernelLaunch(uint32_t quanta);
void osKernelInit(void);
void Task3(void);
	
uint8_t osKernelAddThreads( void(*task0)(void),
														void(*task1)(void),
														void(*task2)(void));

#endif
