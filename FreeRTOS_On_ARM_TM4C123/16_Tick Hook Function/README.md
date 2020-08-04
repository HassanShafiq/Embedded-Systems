### FreeRTOS Tick Hook Function.</br>
This coding implementation demonstrates the FreeRTOS Tick Hook Function using vApplicationTickHook(void). The tick interrupt can optionally call an application defined hook (or callback) function – the tick hook. The tick hook provides a convenient place to implement timer functionality.</br>

The implementation toggles on-board GREEN LED using vTaskDelay() for the task:
- vGreedLedControllerTask(void *pvParamters)</br>

whereas the vApplicationTickHook toggles BLUE LED, when no application task is running on the CPU.

The tick hook will only get called if configUSE_TICK_HOOK is set to 1 within FreeRTOSConfig.h. When this is set the application must provide the hook function with the following prototype:
void vApplicationTickHook( void )

vApplicationTickHook() executes from within an ISR so must be very short, not use much stack, and not call any API functions that don’t end in “FromISR” or “FROM_ISR”.
