### Task Control API in FreeRTOS - Fixed Frequency, Efficient Delays with vTaskDelayUntil (Blocked State).</br>
This coding implementation gives an overview of creating fixed frequency, efficient delays using void vTaskDelayUntil( TickType_t *pxPreviousWakeTime, const TickType_t xTimeIncrement ), available in Task Control API in FreeRTOS using port for Tiva C Launchpad (TM4C123GH6PM).</br>

The implementation toggles on-board LEDs using an accurate delay for 3 tasks with same priorities, by moving them to blocked state: 
- vRedLedControllerTask(void *pvParamters)
- vGreedLedControllerTask(void *pvParamters)
- vBlueLedControllerTask(void *pvParamters)</br>

while the **configTICK_RATE_HZ** is set at 1000Hz (1 milli second time quanta).</br>

This function differs from vTaskDelay() in one important aspect: vTaskDelay() specifies a time at which the task wishes to unblock relative to the time at which vTaskDelay() is called, whereas vTaskDelayUntil() specifies an absolute time at which the task wishes to unblock.

vTaskDelay() will cause a task to block for the specified number of ticks from the time vTaskDelay() is called. It is therefore difficult to use vTaskDelay() by itself to generate a fixed execution frequency as the time between a task unblocking following a call to vTaskDelay() and that task next calling vTaskDelay() may not be fixed [the task may take a different path though the code between calls, or may get interrupted or preempted a different number of times each time it executes].

Whereas vTaskDelay() specifies a wake time relative to the time at which the function is called, vTaskDelayUntil() specifies the absolute (exact) time at which it wishes to unblock.

It should be noted that vTaskDelayUntil() will return immediately (without blocking) if it is used to specify a wake time that is already in the past. Therefore a task using vTaskDelayUntil() to execute periodically will have to re-calculate its required wake time if the periodic execution is halted for any reason (for example, the task is temporarily placed into the Suspended state) causing the task to miss one or more periodic executions. This can be detected by checking the variable passed by reference as the pxPreviousWakeTime parameter against the current tick count. This is however not necessary under most usage scenarios.
