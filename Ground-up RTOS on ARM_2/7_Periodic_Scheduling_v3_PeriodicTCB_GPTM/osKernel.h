#ifndef __OS_KERNEL_H__
#define __OS_KERNEL_H__

#include <stdint.h>

#include "TM4C123.h"                    // Device header


void osKernelLaunch(uint32_t quanta);
void osKernelInit(void);
uint8_t osKernelAddThreads(void(*task0)(void), void(*task1)(void),void(*task2)(void));
uint8_t osKermelAddPeriodicThreads(void (*task)(void), uint32_t period);
void osThreadYield(void);
//void periodicTask_1(void);
//void periodicTask_2(void);

#endif