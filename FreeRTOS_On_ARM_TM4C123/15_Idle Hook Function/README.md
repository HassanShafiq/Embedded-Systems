### FreeRTOS Idle Hook Function.</br>
This coding implementation demonstrates the FreeRTOS Idle Hook Function; a function that is called during each cycle of the idle task using vApplicationIdleHook(void).</br>

The implementation toggles on-board GREEN LED using a pseudo delay for the task:
- vGreedLedControllerTask(void *pvParamters)</br>

whereas the vApplicationIdleHook toggles BLUE LED, when no application task is running on the CPU.

The idle task is created automatically when the RTOS scheduler is started to ensure there is always at least one task that is able to run. It is created at the lowest possible priority to ensure it does not use any CPU time if there are higher priority application tasks in the ready state.
The idle task is responsible for freeing memory allocated by the RTOS to tasks that have since been deleted. It is therefore important in applications that make use of the vTaskDelete() function to ensure the idle task is not starved of processing time. The idle task has no other active functions so can legitimately be starved of microcontroller time under all other conditions.
