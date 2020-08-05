### Configuring FreeRTOS Scheduler - Preemptive Only (FreeRTOSConfig.h).</br>

This coding implementation demonstrate how to configure the FreeRTOS scheduler to work as a Preemptive Scheduler.

All tasks in the application are set at the same prioirty. With preemption enabled using configUSE_PREEMPTION set to 1 (in FreeRTOSConfig.h) file, there is time sharing between application tasks (equal time slices, defualt behaviour of FreeRTOS Kernel) for the CPU time. A task will execute for the amount of time assigned to it and is then preempted to give CPU time to another task in ready queue by the FreeRTOS scheduler.

With preemption enabled using configUSE_PREEMPTION set to 1 and configUSE_TIME_SLICING set to 0 disables timeslicing and the scheduler becomes purely preemptive, where the task with highest priority takes all the CPU time.

In a preemptive scheduler, the tasks at same priority do not preempt each other and the task that is created first in the application takes precedence over the others.
