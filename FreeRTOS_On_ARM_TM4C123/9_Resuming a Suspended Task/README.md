### Task Control API in FreeRTOS - Resuming a suspended task on runtime.</br>
This coding implementation gives an overview of resuming a suspended task, inside of another task using vTaskResume() and task handles, available in Task Control API in FreeRTOS using port for Tiva C Launchpad (TM4C123GH6PM). The implementation also explores the various options available in **FreeRTOSConfig.h** file to configure RTOS scheduler at various modes, task priorities and many other options.</br>

The implementation toggles on-board LEDs using a pseudo delay for 3 tasks with same priorities: 
- vRedLedControllerTask(void *pvParamters)
- vGreedLedControllerTask(void *pvParamters)
- vBlueLedControllerTask(void *pvParamters)</br>

where the tasks use vTaskResume() to resume other tasks, while the **configTICK_RATE_HZ** is set at 1000Hz (1 milli second time quanta).
