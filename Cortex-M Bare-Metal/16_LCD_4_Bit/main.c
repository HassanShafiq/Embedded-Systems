// Including MSIS Device System Header File for TM4C123:
#include "TM4C123.h"                    // Device header

#define			LCD			GPIOB
// Constants for Pins of PortB:
#define			RS			0x01
#define			RW			0x02
#define			EN			0x04

void delay_micro(unsigned int micro);
void delay_milli(unsigned int milli);
void LCD_Write4bits(unsigned char dataANDcommand, unsigned char control);
void LCD4bits_command(unsigned char command);
void LCD4bits_data(unsigned char data);
void LCD4bits_Init(void);
	
int main ()
{
	LCD4bits_Init();
	LCD4bits_command(0x01);		//Clears the screen
	LCD4bits_command(0x08);		//Sets the cursor home
	delay_milli(500);			//delays a bit to let the commands finish
	
	// By default, data is sent one character at a time:
	// Writing>> Cortex-M4:
	LCD4bits_data('C');
	delay_milli(1);
	LCD4bits_data('O');
	delay_milli(1);
	LCD4bits_data('R');
	delay_milli(1);
	LCD4bits_data('T');
	delay_milli(1);
	LCD4bits_data('E');
	delay_milli(1);
	LCD4bits_data('X');
	delay_milli(1);
	LCD4bits_data('-');
	delay_milli(1);
	LCD4bits_data('M');
	delay_milli(1);
	LCD4bits_data('4');
	delay_milli(500);
}


// 4-Bit LCD programming:
// using PORTB such that lower bits PB0-2 signal PB0=RS, PB1=RS, PB2=E
// whereas upper 4 bits PB4-7 signal data

void LCD4bits_Init(void)
{
	//Enable clock to GPIO port
	SYSCTL->RCGCGPIO |= (1U<<1);
	//Set GPIO pins as output pins
	LCD->DIR = 0xFF;
	//Enable GPIO pins
	LCD->DEN = 0xFF;
	
	//Function set command: 0x28 = 4-bit, 2 display lines, 5x7 font
	LCD4bits_command(0x28);
	//Entry mode set command: 0x06 = increment automatically
	LCD4bits_command(0x06);
	//Display control: 0x01 = clear dispaly
	LCD4bits_command(0x01);
	//Display control: 0x0F = turn on display, cursor blinking
	LCD4bits_command(0x0F);
}

void LCD_Write4bits(unsigned char dataANDcommand, unsigned char control)
{
	//Extract upper 4 bits for data
	dataANDcommand &= 0xF0; // dataANDcommand = (data & 0xFF)
	
	//Extract lower 4 bits for control configuration
	control &= 0x0F; // control = (control & 0x0F)

	//Write data and control to PortB
	LCD->DATA = dataANDcommand | control;
	
	//Secure data and command by pulsing E pin
	LCD->DATA = dataANDcommand | control | EN;
	delay_micro(0);
	LCD->DATA = dataANDcommand;
	
	//Clear the LCD port
	
}

void LCD4bits_command(unsigned char command)
{
	//Write upper 4-bits of command
	LCD_Write4bits(command & 0xF0, 0);
	
	//Write lower 4-bits of command
	LCD_Write4bits(command<<4, 0);
	
	//Secure command
	if (command<4)
		delay_milli(2);
	else
		delay_milli(40);
}

void LCD4bits_data(unsigned char data)
{
	//Write upper 4-bits of data
	LCD_Write4bits(data & 0xF0, RS); // RS = 0x01
	
	//Write lower 4-bits of data
	LCD_Write4bits(data<<4, RS);
	//Secure data
	delay_micro(40);
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
