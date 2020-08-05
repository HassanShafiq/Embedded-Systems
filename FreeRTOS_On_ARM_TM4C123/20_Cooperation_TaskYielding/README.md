### Configuring FreeRTOS Scheduler - Cooperative Scheduling or Cooperative Task Yielding (FreeRTOSConfig.h and RTOS Kernel Control API).</br>

This coding implementation demonstrate how to configure the FreeRTOS scheduler using taskYield() (in RTOS Kernel Control API), to work as a Cooperative Scheduling or Cooperative Task Yielding scheduler.

All application tasks are at the same priority of level 1. 

With preemption enabled using configUSE_PREEMPTION set to 1 and configUSE_TIME_SLICING set to 0 timeslicing is disabled and the scheduler becomes purely preemptive, where the task with highest priority or first task in the order of creation, in case of same priority level, takes all the CPU time.

However, we call taskYield() in each tasks to make them voluntarily yield processor, hence the tasks become cooperative.

This implementation results in a scheduler that exhibits Pseudo Timesharing by using task cooperation.
  
