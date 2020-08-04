### Task Creation API in FreeRTOS - Using task parameters.</br>
This coding implementation gives an overview of using task parameters (void *pvParameters) in FreeRTOS using port for Tiva C Launchpad (TM4C123GH6PM), demonstrating how to pass different parameters to tasks with same implementation with different names. This implementation demonstrate how to avoid a boilerplate consisting of copies of same task only differing in parameters and impement them efficiently.</br>

xTaskCreate() in main() creates 3 tasks using same pointer to task entry function; vLedControllerTask, however, passing different LED #s using *pvParameters for each.</br>

This in turn creates 3 tasks that use the same task entry function but behave differently, toggling on-board LEDs using a pseudo delay, while the **configTICK_RATE_HZ** is set at 1000Hz (1 milli second time quanta).
