### Task Creation API in FreeRTOS - Creating task from inside of another task.</br>
This coding implementation gives an overview of creating tasks inside of another task in FreeRTOS using port for Tiva C Launchpad (TM4C123GH6PM), giving an overview of how an RTOS Scheduler works and its various components. The implementation also explores the various options available in **FreeRTOSConfig.h** file to configure RTOS scheduler at various modes and many other options.</br>

xTaskCreate() in main() creates vBlueLedControllerTask(void *pvParamters) before scheduler starts by invoking vTaskStartScheduler(). vBlueLedControllerTask(void *pvParamters) in turn creates:
- vRedLedControllerTask(void *pvParamters)
- vGreedLedControllerTask(void *pvParamters)</br>

toggling on-board LEDs using a pseudo delay, while the **configTICK_RATE_HZ** is set at 1000Hz (1 milli second time quanta).
