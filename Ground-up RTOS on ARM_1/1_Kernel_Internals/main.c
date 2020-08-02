#include "TM4C123.h"                    // Device header
#include<stdint.h>

#define		RED			0x02
#define		BLUE		0x04
#define 	GREEN		0x08
#define		SYSCONTROL_RCC_R		(*((volatile unsigned long *)0x400FE060))
#define		SYSCONTROL_RCC2_R		(*((volatile unsigned long *)0x400FE060))
#define		MOSCCTL_R						(*((volatile unsigned long *)0x400FE07C))
//#define 	Stack_Pointer				SP

void GPIO_Init(void);
void main_RED(void);
void main_BLUE(void);
void main_GREEN(void);
void delay (unsigned int millis);
void SysTick_Init();
void SysTick_Handler(void);

uint32_t coreClock_1 = 0;                       /* Variables to store core clock values */
uint32_t coreClock_2 = 0;

unsigned int int_size;
unsigned int number = 0x87654321;
unsigned long RCC_Value_before;
unsigned long RCC_Value_after;
unsigned long RCC2_Value_before;
unsigned long RCC2_Value_after;
unsigned long MOSCCTL_Value;
volatile uint32_t tick;
volatile uint32_t _tick;

// Stack Declaration to hold the Cortex-M Registers Stack Frame upon Exception:
uint32_t green_STACK[40];
uint32_t blue_STACK[40];

uint32_t *sp_green = &green_STACK[40];
uint32_t *sp_blue	 = &blue_STACK[40];

int main (void)
{
	int size_test;
	int_size = sizeof(size_test);
	int start = 0;
//	RCC_Value_before = SYSCONTROL_RCC_R & 0xFFFFFFFF;
//	RCC2_Value_before = SYSCONTROL_RCC2_R & 0xFFFFFFFF;
	GPIO_Init();
	SysTick_Init();
	
	// Initializing the stack frame for main_GREEN():
	*(--sp_green) = (1U << 24);									// xPSR --- Setting bit-24 of xPSR register to instruct TM4C core to run in Thumb2 mode.
	*(--sp_green)	= (uint32_t) &main_GREEN;			// PC
		*(--sp_green)	= 0x0000000DU;							// LR --- These registers can be initialized with random values.
		*(--sp_green)	= 0x0000000EU;							// R12
		*(--sp_green)	= 0x0000000AU;							// R3
		*(--sp_green)	= 0x0000000EU;							// R2
		*(--sp_green)	= 0x0000000AU;							// R1
		*(--sp_green)	= 0x0000000DU;							// R0 - Top of the Stack, Post-IRQ
	
	// Initializing the stack frame for main_BLUE():
	*(--sp_blue) = (1U << 24);									// xPSR --- Setting bit-24 of xPSR register to instruct TM4C core to run in Thumb2 mode.
	*(--sp_blue)	= (uint32_t) &main_BLUE;			// PC
		*(--sp_blue)	= 0x0000000DU;							// LR --- These registers can be initialized with random values.
		*(--sp_blue)	= 0x0000000EU;							// R12
		*(--sp_blue)	= 0x0000000AU;							// R3
		*(--sp_blue)	= 0x0000000EU;							// R2
		*(--sp_blue)	= 0x0000000AU;							// R1
		*(--sp_blue)	= 0x0000000DU;							// R0 - Top of the Stack, Post-IRQ
	
	
	
//	coreClock_1 = SystemCoreClock;                /* Store value of predefined SystemCoreClock */
//	SystemCoreClockUpdate();                      /* Update SystemCoreClock according to register settings */
//	coreClock_2 = SystemCoreClock;                /* Store value of calculated SystemCoreClock */
//	
//	RCC_Value_after = SYSCONTROL_RCC_R & 0xFFFFFFFF;
//	RCC2_Value_after = SYSCONTROL_RCC2_R & 0xFFFFFFFF;
//	MOSCCTL_Value = MOSCCTL_R & 0xFFFFFFFF;
//	
//	coreClock_2 = SystemCoreClock;
	while(1)
	{
		
	}
}

void GPIO_Init(void)
{
	SYSCTL->RCGCGPIO		|=	0x20;
	GPIOF->DIR					|=	0x0E;
	GPIOF->DEN					|=	0x0E;
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000U);
}

void main_RED(void)
{
	while(1)
	{
		GPIOF->DATA		|=		RED;
		delay(1000);
		GPIOF->DATA		=		0x00;
		delay(1000);
	}
}

void main_BLUE(void)
{
	while(1)
	{
		GPIOF->DATA		|=		BLUE;
		delay(1);
		GPIOF->DATA		=		0x00;
		delay(1);
	}
}

void main_GREEN(void)
{
	while(1)
	{
		GPIOF->DATA		|=		GREEN;
		delay(1);
		GPIOF->DATA		=		0x00;
		delay(1);
	}
}

void SysTick_Init()
{
	SysTick->CTRL		= 0x00;				//Disable SysTick to configure
	SysTick->LOAD		= 0x00F42400;	// 0xF42400 = 16000000.
	SysTick->VAL		= 0x00;
	SysTick->CTRL		= 0x07;
	__enable_irq();
}

void SysTick_Handler(void)
{
	//GPIOF->DATA		^=	~(GREEN | BLUE);
	tick++;
}

uint32_t getTicks(void)
{
	__disable_irq();
	_tick = tick;
	__enable_irq();
	
	return _tick;
}

void delay (uint32_t seconds)
{
	seconds		*= 1;
	uint32_t	temp	= getTicks();
	while((getTicks() - temp) < seconds)
	{
		//Blocking Code
	}
}