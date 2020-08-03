This excercise is to build a peripheral driver purely in Cortex-M assembley code.

It initializes the GPIO Port F through 
- SYSCTL_RCGCGPIO_R
- GPIO_PORTF_DIR_R
- GPIO_PORTF_DEN_R
- GPIO_PORTF_PUR_R
- GPIO_PORTF_LOCK_R
- GPIO_PORTF_CR_R
- RED LED Pin</br>
registers and toggles it upon pressing the on-board press buttons.

Concepts regarding initialization steps (startup_TM4C123.s and startup_TM4C123.c) in Cortex-M's startup routine before entering main() routine are also discussed.
