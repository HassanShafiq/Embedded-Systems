### Task Creation API in FreeRTOS - Killing a task.</br>
This coding implementation gives an overview of killing a task using vTaskDelete( TaskHandle_t xTask ) in Task Creation API in FreeRTOS using port for Tiva C Launchpad (TM4C123GH6PM), giving an overview of how an RTOS Scheduler works and its various components.</br>

The implementation toggles on-board LEDs using a pseudo delay for 3 tasks: 
- vRedLedControllerTask(void *pvParamters)
- vGreedLedControllerTask(void *pvParamters)
- vBlueLedControllerTask(void *pvParamters)</br>

whereas after certain number of executions, vRedLedControllerTask() is deleted, while the **configTICK_RATE_HZ** is set at 1000Hz (1 milli second time quanta).

INCLUDE_vTaskDelete must be defined as 1 for this function to be available. See the RTOS Configuration documentation for more information.

Remove a task from the RTOS kernels management. The task being deleted will be removed from all ready, blocked, suspended and event lists.
