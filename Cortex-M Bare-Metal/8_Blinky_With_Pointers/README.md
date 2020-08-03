This exercise includes 3 main.c files:</br>

- **main.c** file uses the concept of a pointer variable to point to various peripheral registers and performs peripheral initialization for PF3-1 for Cortex-M (TM4C123GH6PM here), leaving them in ON state.
- **main_2.c** file uses tm4c123gh6pm.h file (vendor's hardware peripheral register definitions file), accessing peripheral registers using TI's naming convention, performing initialization of PF2 andtoggling with a pseudo delay using while() loop blocking code.
- **main_3.c** file file uses tm4c123gh6pm.h file (vendor's hardware peripheral register definitions file), accessing peripheral registers using TI's naming convention, performing initialization of PF3-1 and toggling with a pseudo delay using while() loop blocking code.
