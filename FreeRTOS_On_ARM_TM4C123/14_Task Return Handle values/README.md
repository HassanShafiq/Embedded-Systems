### Task Return Handle values (return type of xTaskCreate() function).</br>
This coding implementation experiments with the Task Return Handle values which is the return type of xTaskCreate() function available in Task Creation API in FreeRTOS using port for Tiva C Launchpad (TM4C123GH6PM), giving an overview of how an RTOS Scheduler works and its various components.</br>

The implementation toggles on-board LEDs using a pseudo delay for 3 tasks: 
- vRedLedControllerTask(void *pvParamters)
- vGreedLedControllerTask(void *pvParamters)
- vBlueLedControllerTask(void *pvParamters)</br>

The value of task return handle can be used to determine the status of task creation API call. If the task was created successfully then pdPASS (= 1) is returned. Otherwise errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY (= -1) is returned.
