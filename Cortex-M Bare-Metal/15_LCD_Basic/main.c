// Including MSIS Device System Header File for TM4C123:
#include "TM4C123.h"                    // Device header


void LCD_Init();
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void delay_micro(unsigned int micro);
void delay_milli(unsigned int milli);
	
int main ()
{
	LCD_Init();
	LCD_command(0x01);		//Clears the screen
	LCD_command(0x08);		//Sets the cursor home
	delay_milli(500);			//delays a bit to let the commands finish
	
	// By default, data is sent one character at a time:
	// Writing>> Cortex-M4:
	LCD_data('C');
	delay_milli(1);
	LCD_data('O');
	delay_milli(1);
	LCD_data('R');
	delay_milli(1);
	LCD_data('T');
	delay_milli(1);
	LCD_data('E');
	delay_milli(1);
	LCD_data('X');
	delay_milli(1);
	LCD_data('-');
	delay_milli(1);
	LCD_data('M');
	delay_milli(1);
	LCD_data('4');
	delay_milli(500);
}

void LCD_Init()
{
	//Enable GPIO Port Clock:
	SYSCTL->RCGCGPIO = 0x01; //Port A: for LCD Controls
	SYSCTL->RCGCGPIO |= 0x02; //Port B: for LCD Data Lines
	GPIOA->DIR |= 0x0E; // For PA5-7 for LCD Controls: RS, RW, E.
	GPIOA->DEN |= 0xE0;
	GPIOB->DIR |= 0xFF; // For PB0-1 for LCD Data Lines.
	GPIOB->DEN |= 0xFF;
	LCD_command(0x38);		//8-bits mode, 2 line display, 5x7 font
	LCD_command(0x06);		//incrment automatically
	LCD_command(0xFF);		//Turn on the Display
	LCD_command(0x01);		//Clear Display
}

void LCD_command(unsigned char command)
{
	//Select Internal Command Register:
	GPIOA->DATA = 0x00; // RS=0, RW=0, E=0
	GPIOB->DATA = command; // Write Command throug lines PB0-7
	GPIOA->DATA = 0x80; // writing E=1, to secure command
	delay_micro(0);
	GPIOA->DATA = 0x00; // Setting back to command register
	// Conditional execution of delays depending upon the delay requirements of the command:
	if (command < 4)
		delay_milli(2);
	else
		delay_micro(37);
	
	
}

void LCD_data(unsigned char data)
{
	//Selecct Internal Data Regsiter:
	GPIOA->DATA = 0x20; // RS=0, RW=0, E=0
	GPIOB->DATA = data;	// Through lines PB0-7
	GPIOA->DATA |= 0x80; // writing E=1, to secure command
	delay_micro(0);
	GPIOA->DATA = 0x00; // Setting back to command register
	delay_micro(0);
}

void delay_micro(unsigned int micro)
{
	for (int i = 0; i < 4; i++)
	{
		// Do nothing
	}
}

void delay_milli(unsigned int milli)
{
	for (int i = 0; i < 4000; i++)
	{
		// Do nothing
	}
}

