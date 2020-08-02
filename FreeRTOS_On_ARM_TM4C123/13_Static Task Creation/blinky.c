//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED using direct register
//! access.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

//*****************************************************************************
//
// Task Handlers Prototypes:
//
//*****************************************************************************
void vBlueLedControllerTask(void *pvParamters);
void vRedLedControllerTask(void *pvParamters);
void vGreenLedControllerTask(void *pvParamters);

// Defining Task Stack Sizes:
#define blueTask_STACK_SIZE 100
StaticTask_t xBlueLedControllerTaskBuffer; //Task Control Block (TCB) Buffer
StackType_t xBlueLedControllerStack[blueTask_STACK_SIZE]; // Equivalent to uint32_t xBlueLedControllerStack[blueTask_STACK_SIZE]

#define greenTask_STACK_SIZE 100
StaticTask_t xGreenLedControllerTaskBuffer; //Task Control Block (TCB) Buffer
StackType_t xGreenLedControllerStack[greenTask_STACK_SIZE]; // Equivalent to uint32_t xBlueLedControllerStack[blueTask_STACK_SIZE]

#define redTask_STACK_SIZE 100
StaticTask_t xRedLedControllerTaskBuffer; //Task Control Block (TCB) Buffer
StackType_t xRedLedControllerStack[redTask_STACK_SIZE]; // Equivalent to uint32_t xBlueLedControllerStack[blueTask_STACK_SIZE]

// Task Handling Blocks:
TaskHandle_t blue_Handle, red_Handle, green_Handle;
uint32_t	suspendMonitor = 0;
uint32_t	resumeMonitor = 0;
bool 			_suspended = false;

uint32_t	CNTRL_DELAY = 1000000;
TaskHandle_t 	task_created;
//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
int main(void)
{
		volatile uint32_t ui32Loop;
		volatile uint8_t pinValue_1;
		volatile uint8_t pinValue_2;
		volatile uint8_t pinValue_3;
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }
		
    //
    // Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3); // GREEN LED
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2); // BLUE LED
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1); // RED LED
		
		// Creating Blue Task Statically:
		// Static Task Creation is not enabled by default in FreeRTOS
		task_created = xTaskCreateStatic(vBlueLedControllerTask,
																		"Blue Led Controller",
																		blueTask_STACK_SIZE,
																		NULL,
																		1,
																		xBlueLedControllerStack,
																		&xBlueLedControllerTaskBuffer);
		if (task_created)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
      for(ui32Loop = 0; ui32Loop < 10000000 ; ui32Loop++)
      {
      }
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
		}
		
		task_created = xTaskCreateStatic(vGreenLedControllerTask,
																		"Green Led Controller",
																		greenTask_STACK_SIZE,
																		NULL,
																		1,
																		xGreenLedControllerStack,
																		&xGreenLedControllerTaskBuffer);
		if (task_created)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
      for(ui32Loop = 0; ui32Loop < 10000000 ; ui32Loop++)
      {
      }
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
		}
		
		task_created = xTaskCreateStatic(vRedLedControllerTask,
																		"Red Led Controller",
																		redTask_STACK_SIZE,
																		NULL,
																		1,
																		xRedLedControllerStack,
																		&xRedLedControllerTaskBuffer);
		if (task_created)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
      for(ui32Loop = 0; ui32Loop < 10000000 ; ui32Loop++)
      {
      }
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
		}
		
		for(ui32Loop = 0; ui32Loop < 10000000 ; ui32Loop++)
    {
    }
		
		vTaskStartScheduler();

    //
    // Loop forever.
    //
		 pinValue_3 = GPIO_PIN_3;
		 pinValue_2 = GPIO_PIN_2;
		 pinValue_1 = GPIO_PIN_1;
		 while(1)
		 {
			 //
					// Turn on the LED.
					//
			 
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, pinValue_3);
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, pinValue_2);
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, pinValue_1);
					pinValue_1 = ~pinValue_1;
					pinValue_2 = ~pinValue_2;
					pinValue_3 = ~pinValue_3;
					
					//
					// Delay for a bit.
					//
					for(ui32Loop = 0; ui32Loop < 1000000 ; ui32Loop++)
					{
					}
		 }
}


void vGreenLedControllerTask(void *pvParamters)
{
	 volatile uint32_t ui32Loop;
	 volatile uint8_t pinValue;
	 
	 pinValue = GPIO_PIN_3;
	 while(1)
	 {
		 //
        // Turn on the LED.
        //
		 
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, pinValue);
				pinValue = ~pinValue;
				
        //
        // Delay for a bit.
        //
        for(ui32Loop = 0; ui32Loop < CNTRL_DELAY ; ui32Loop++)
        {
        }/*
				suspendMonitor++;
				if (suspendMonitor >= 40)
				{
					_suspended = true;
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
					vTaskSuspend(NULL);
				}*/
	 }
}

void vBlueLedControllerTask(void *pvParamters)
{
	 volatile uint32_t ui32Loop;
	 volatile uint8_t pinValue;
	 
	 pinValue = GPIO_PIN_2;
	 while(1)
	 {
		 //
        // Turn on the LED.
        //
		 
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, pinValue);
				pinValue = ~pinValue;
				
        //
        // Delay for a bit.
        //
        for(ui32Loop = 0; ui32Loop < CNTRL_DELAY ; ui32Loop++)
        {
        }/*
				suspendMonitor++;
				if (suspendMonitor >= 80)
				{
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
					vTaskResume(red_Handle);
					vTaskSuspend(blue_Handle);
				}*/
	 }
}

void vRedLedControllerTask(void *pvParamters)
{
	 volatile uint32_t ui32Loop;
	 volatile uint8_t pinValue;
	 
	 pinValue = GPIO_PIN_1;
	 while(1)
	 {
		 //
        // Turn on the LED.
        //
		 
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, pinValue);
				pinValue = ~pinValue;
				
        //
        // Delay for a bit.
        //
        for(ui32Loop = 0; ui32Loop < CNTRL_DELAY ; ui32Loop++)
        {
        }/*
				suspendMonitor++;
				if (suspendMonitor >= 120)
				{
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
					suspendMonitor = 0;
					if (_suspended == true)
					{
						vTaskResume(green_Handle);
						vTaskResume(blue_Handle);
					}
					
					//Killing red task:
					vTaskDelete(red_Handle);
				}*/
	 }
}

/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
			implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
			used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
	/* If the buffers to be provided to the Idle task are declared inside this
	function then they must be declared static – otherwise they will be allocated on
	the stack and so not exists after this function exits. */
	static StaticTask_t xIdleTaskTCB;
	static StackType_t	uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];
	
	/* Pass out a pointer to the StaticTask_t structure in which the Idle task’s state will be stored. */
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
	/* Pass out the array that will be used as the Idle task’s stack. */
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;
	/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
	Note that, as the array is necessarily of type StackType_t, configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static – otherwise they will be allocated on
the stack and so not exists after this function exits. */
	static StaticTask_t xTimerTaskTCB;
	static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];



    /* Pass out a pointer to the StaticTask_t structure in which the Timer task’s state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task’s stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;

}