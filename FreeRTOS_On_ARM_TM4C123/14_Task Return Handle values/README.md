### Task Return Handle values.</br>
This coding implementation gives an overview of creating a task statically using xTaskCreateStatic(), available in Task Creation API in FreeRTOS using port for Tiva C Launchpad (TM4C123GH6PM), giving an overview of how an RTOS Scheduler works and its various components.</br>

The implementation toggles on-board LEDs using a pseudo delay for 3 tasks: 
- vRedLedControllerTask(void *pvParamters)
- vGreedLedControllerTask(void *pvParamters)
- vBlueLedControllerTask(void *pvParamters)</br>

created using xTaskCreateStatic() and be provided a pre-allocated memory pool for the Task Stacks and Task Control Block (TCB) buffers, while the **configTICK_RATE_HZ** is set at 1000Hz (1 milli second time quanta).

Create a new task and add it to the list of tasks that are ready to run. configSUPPORT_STATIC_ALLOCATION must be set to 1 in FreeRTOSConfig.h for this RTOS API function to be available.

Each task requires RAM that is used to hold the task state, and used by the task as its stack. If a task is created using xTaskCreate() then the required RAM is automatically allocated from the FreeRTOS heap. If a task is created using xTaskCreateStatic() then the RAM is provided by the application writer, which results in a greater number of parameters, but allows the RAM to be statically allocated at compile time. See the Static Vs Dynamic allocation page (https://www.freertos.org/Static_Vs_Dynamic_Memory_Allocation.html) for more information.
