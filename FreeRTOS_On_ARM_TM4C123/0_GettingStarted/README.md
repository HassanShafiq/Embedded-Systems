### Converting an existing application into a FreeRTOS Real-time application.</br>
This coding implementation converts an existing LED blinky application into a FreeRTOS Real-time application using FreeRTOS port for Tiva C Launchpad (TM4C123GH6PM), giving an overview of how an RTOS Scheduler works and its various components. The implementation also explores the various options available in **FreeRTOSConfig.h** file to configure RTOS scheduler at various modes and many other options.</br>

The implementation toggles on-board LEDs using a pseudo delay for 3 tasks: 
- vRedLedControllerTask(void *pvParamters)
- vGreedLedControllerTask(void *pvParamters)
- vBlueLedControllerTask(void *pvParamters)</br>

while the **configTICK_RATE_HZ** is set at 1000Hz (1 milli second time quanta).
