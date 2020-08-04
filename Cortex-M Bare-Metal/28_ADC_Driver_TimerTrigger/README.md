## ADC Driver - Timer Triggered converion, reading on-chip temperature sensor value</br>
This project implements an ADC Driver that uses Timer-Triggered (32-bit Wide Timer 0, configured as Periodic down-counter) on Pin 3 of Port E (PE 3) using Sample Sequencr 3 (SS3) of ADC Module 0, to read and convert the value of on-chip temperature sensor of TM4C core, running at 16MHz

ADC0 EMUX register is configured for Timer-Triggered based ADC Conversion. To detect the end-of-conversion, bit-3 of ADC0 RIS register is polled and tested infinitely, until conversion ends and then the value of ADC0 conversion is read from SSFIFO3 register at 12-bit resolution.
