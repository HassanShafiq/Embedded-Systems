## GPTM Multiple Interrupts (Pseudo Real-time system)</br>
This project implements two GPTM interrupts of different frequencies (1Hz and 10Hz) using two different GPTM blocks (Timer1 A and Timer2 A), both configured as a 16-bit down-counter, with TM4C core running at 16 MHz.</br>

This exhibits the implementation of a pseudo real-time system with 3 different threads, one main() thread (foreground) and two Timer Interrupt Handlers (background threads), running on the same CPU core. Timer1A_Handler() toggles on-board RED LED at 1Hz and Timer2A_Handler() toggles GREEN LED at 10Hz, whereas the main() thread toggles BLUE LED once a second.
