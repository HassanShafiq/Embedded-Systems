# Embedded-System
This repository contains my coding implementations for Udemy based Embedded Systems and RTOS courses.<br/>**Development Board used:** EK-TM4C123GXL based on TM4C123GH6PM MCU (Texas Instruments).

Performing a range of coding projects, key skills that I learnt:<br/>
- Low-level device drivers development (bare-metal), to interface on-chip peripherals with various external I/O hardware (sensors/actuators)<br/>
-	Compiler intrinsics, assembly code optimization and exploiting NVIC features for low-interrupt latency<br/>
-	Hardware/software debugging, concept of Finite State Machine (FSM) and embedded software development process<br/>
-	Board Support Package (BSP) and Application development in embedded OS environments (FreeRTOS especially)<br/>
-	Overview of the features of various market leading embedded OS (Micrium  µC/OS-III, CMSIS RTOS RTX, FreeRTOS)<br/>
-	Understanding with the internals of an OS kernel, thread-scheduling schemes and OS porting considerations to other MCUs in ARM product family<br/>

These dedicated courses have also provided me a comprehensive understanding of IDE/Compiler Toolchains, ARM design philosophy, programmer's model & firmware development principles in ARM's ecosystem along with internal features of the Cortex-M/A that support embedded OS deployment. This exercise provided me experience in navigating through architecture/technical reference manuals, generic user guides, device data Sheets, and schematics professionally. This helped me learn the algorithmic approaches in resolving a challenge to get an embedded project up & running or alternatively, debug one.<br/>

---------------------------------------------------------------------------------

### **~\Cortex-M Bare-Metal<br/>**
Contains implementations for the course: **Complete ARM Cortex-M Bare-Metal Programming Ground Up™**

This course teaches Cortex-M Internals, Pointers, Structures, Memory Navigation, Debugging, CMSIS,Assembly etc and how to navigate the microntroller reference manual and datasheet to extract the right  information to professionally  build peripheral drivers (ADC, UART, GPIO, TIMER etc.) and firmware. To achieve this goal, no libraries are used in this course, purely ARM Assembly Language and bare-metal embedded C.

---------------------------------------------------------------------------------
### **~\FreeRTOS_On_ARM_TM4C123<br/>**
Contains implementations for the course: **FreeRTOS From Ground Up™ on ARM Processors**

This course teaches the foundations of real-time systems and how to build real-time applications using FreeRTOS ,one of the most popular real-time operating systems  for embedded systems.  The course gives a detailed overview of the characteristics of the FreeRTOS real-time kernel,  provides a detailed tutorial on the APIs to implement the various features of FreeRTOS  and then goes on to build about 50 real-time projects.

---------------------------------------------------------------------------------

### **~\Ground-up RTOS on ARM_1<br/>**

Contains implementations for the course: **Build Your Own RealTime OS (RTOS) From Ground Up™ on ARM 1**

This course teaches how to build a Real-Time Operating Systems through intensive practice and theory. It starts by getting you excited through an introduction to the internals of a Real-Time Kernel on ARM Processors, which you shall implement yourself in code.Then we move on to learn all there  is about Real-Time Operating Systems, their various parts, how they work and then we finally build our own Real-Time Operating System exploring different scheduling algorithms and Inter-Thread communication tools.

---------------------------------------------------------------------------------

### **~\Ground-up RTOS on ARM_2 (Advanced Concepts)<br/>**

Contains implementations for the course: **Build Your Own RealTime OS (RTOS) From Ground Up™ on ARM 2**

This course teaches how to build a Real-Time Operating Systems through intensive practice and theory. It starts by getting you excited through an introduction to the internals of a Real-Time Kernel on ARM Processors, which you shall implement yourself in code.Then we move on to learn all there  is about Real-Time Operating Systems, their various parts, how they work and then we finally build our own Real-Time Operating System exploring different scheduling algorithms and Inter-Thread communication tools.

---------------------------------------------------------------------------------

**Important Note:**<br/>
At the time of initializing this README.md file, the author of these above mentioned courese; Israel Gbati (https://www.udemy.com/user/israel-gbati-2/) is going through some re-orientation on Udemy to launch his own separate eLearning platform for Embedded Systems (at www.cortex-m.com). Therefore, direct access to the details of these course is temporarily unavailble publicly. However, those who had purchased them already (as I do), have lifetime full access. In case, interested to see section-wise details of the courses, please ask me and I'll share access.
