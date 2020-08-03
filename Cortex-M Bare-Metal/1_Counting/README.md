This coding exercise is to understand internals of Cortex-M (TM4C123GH6PM) when our program is running, such as the values that are placed in registers, the changes that happen in the memory, how to make code run faster and many other concepts.</br></br>
This excercise introduces to the following concepts: 
- Debug view of Keil uVision
- memory views
- wwatch windows
- Cortex-M memory map
- an inside look into how conditional statements behave in Cortex-M
- global variable and RAM storage
- Big Endian vs Little Endian
- accessing a particular RAM location and dropping a BEEF (0x0000BEEF) value there

The coding implementatin is very simple, including an incrementing counter. However, the mentioned internals have to be observed in Debug mode.
