### Configuring FreeRTOS Scheduler - Pseudo Timesharing by Blocking Tasks(FreeRTOSConfig.h).</br>

This coding implementation demonstrate how to configure the FreeRTOS scheduler to work as a Pseudo Timesharing scheduler by blocking other tasks.

vGreenLedControllerTask in the application is set at the same higherst priority while vRedLedControllerTask and vBlueLedControllerTask are at lower, same priority level. 

With preemption enabled using configUSE_PREEMPTION set to 1 and configUSE_TIME_SLICING set to 0 disables timeslicing and the scheduler becomes purely preemptive, where the task with highest priority takes all the CPU time.

However, we use vTaskDelay() in each tasks to block them for certain period of time, hence higher priority task relinquishes process and let's lower priority tasks to gain CPU time also.

This implementation results in a scheduler that exhibits Pseudo Timesharing by blocking tasks at higher priority.
