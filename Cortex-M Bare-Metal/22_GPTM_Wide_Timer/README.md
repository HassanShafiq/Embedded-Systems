## GPTM Wide Timer (32-bit) Implementation</br>
This exercise introduces General Purpose Timers (GPTM peripheral) on Tiva C Lanuchpad (TM4C123GH6PM) and uses a 32-bit Wide-Timer configured as Periodic down-counter for Timer Module 1, toggling on-board BLUE LED by polling WTIMER1 RIS register bit-1 inside Wide_Timer1A_DelaySec(int seconds) function, while TM4C core is running at 16MHz
