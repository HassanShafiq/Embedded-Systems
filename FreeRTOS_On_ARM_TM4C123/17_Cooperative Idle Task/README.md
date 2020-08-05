### FreeRTOS Cooperative Idle Task.</br>
This coding implementation demonstrates the of FreeRTOS Cooperative Idle Task Function using vApplicationIdleHook(void) and how its yield configuration with configIDLE_SHOULD_YIELD (in FreeRTOSConfig.h file) effects the time sharing between application tasks and the idle task. The tick interrupt can optionally call an application defined hook (or callback) function – the tick hook. The tick hook provides a convenient place to implement timer functionality.</br>

The implementation toggles on-board GREEN LED using vTaskDelay() for the task:
- vGreedLedControllerTask(void *pvParamters)</br>

and increments greenCounter whereas the vApplicationTickHook toggles BLUE LED and increments idleCounter, when no application task is running on the CPU.

Both tasks are set at same priority level. Since, the scheduler is not configured as purely Round-Robin, we don't know in prior the time-slice each task gets from the schedluer. Therefore configuring configIDLE_SHOULD_YIELD to 1 will enable yielding for idle task (vApplicationIdleTask), execute it's instructions once and then yield. Hence, vGreedLedControllerTask() will get considerably more processor time than vApplicationIdleHook().

Configuring configIDLE_SHOULD_YIELD to 0 disables yielding for vApplicationIdleHook() and it gets fairly equal time compared to vGreenLedControllerTask() being at same prioriry level.
