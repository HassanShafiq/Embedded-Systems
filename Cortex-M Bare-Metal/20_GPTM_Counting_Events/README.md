## GPTM Event-Counter Mode Implementation</br>
This exercise introduces General Purpopose Timers (GPTM peripheral) on Tiva C Lanuchpad (TM4C123GH6PM) and uses a 16-bit Timer2 A configured as Event-Counter on Rising Edge of every clock cycle by infinitely calling Timer2A_RisingEdgeEvent_Capture() inside a while(1) looop and reading Timer2 TAR register value, with TM4C core running at 16MHz.
