### Task Creation API in FreeRTOS - Using task parameters.</br>
This coding implementation gives an overview of using task parameters (void *pvParameters) in FreeRTOS using port for Tiva C Launchpad (TM4C123GH6PM), demonstrating how to pass different parameters to tasks with same implementation with different parameters only. This implementation demonstrate how to avoid a boilerplate consisting of copies of same task only differing in parameters and hence impement efficiently in terms of code size.</br>

xTaskCreate() in main() creates 3 tasks using a pointer to the same task entry function; vLedControllerTask, however, passing different LED Pin #s using *pvParameters for each task creation.</br>

This in turn creates 3 tasks that use the same task entry function but behave differently because of different paramter(s) passed, toggling on-board LEDs using a pseudo delay, while the **configTICK_RATE_HZ** is set at 1000Hz (1 milli second time quanta).
