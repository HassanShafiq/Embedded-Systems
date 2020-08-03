## GPTM Interrupt</br>
This exercise implements GPIO interrupt, configuring PF4 (SW1), PF0 (SW0) for falling-edge interrupt trigger through GPIO Interrupt Sense (GPIOIS), GPIO Interrupt Event (GPIOIEV), GPIO Interrupt Clear (GPIOICR) registers, setting priority and enabling interrupts in NVIC registers. Interrupt toggles PF3 (LED Pin 3) in GPIOF_Handler().
