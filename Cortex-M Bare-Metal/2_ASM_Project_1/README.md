This excercise is to build a peripheral driver purely in **Cortex-M assembley code**.</br></br>
It initializes the GPIO Port F through SYSCTL_RCGCGPIO_R, GPIO_PORTF_DIR_R, GPIO_PORTF_DEN_R only, RED LED Pin and simply turns it in ON state.

Concepts regarding initialization steps (startup_TM4C123.s and startup_TM4C123.c) in Cortex-M's startup routine before entering main() routine are also discussed.
