/***
****************************************************************
* @file    TM4C123_RTOS_BSP.c
* @author  Hassan Shafiq
* @version V1.0
* @brief   Selected Drivers for TM4C123
*          +RCC
*          +GPTimer1A 
*          +GPIOC 
*          +SSI0
*					 +ADC0
*					 +WTimer5
*					 +GPTimer3

 @verbatim
 ===================================================================================

	@endverbatim 
***********************************************************************/

#ifndef __TM4C123_RTOS_BSP_H
#define __TM4C123_RTOS_BSP_H
//#include "GLCD_ST7735.h"

#include <stdint.h>

/*************RCC Register Configuration values**************************/



#define SYSCTL_RCC2_USERCC2     0x80000000  // Use RCC2
#define SYSCTL_RCC2_DIV400      0x40000000  // Divide PLL as 400 MHz vs. 200
                                            // MHz

#define SYSCTL_RCC2_PWRDN2      0x00002000  // Power-Down PLL 2
#define SYSCTL_RCC2_BYPASS2     0x00000800  // PLL Bypass 2
#define SYSCTL_RCC2_OSCSRC2_M   0x00000070  // Oscillator Source 2
#define SYSCTL_RCC2_OSCSRC2_MO  0x00000000  // MOSC

#define SYSCTL_RCC_XTAL_M       0x000007C0  // Crystal Value
#define SYSCTL_RCC_XTAL_16MHZ   0x00000540  // 16 MHz
#define SYSCTL_RIS_PLLLRIS      0x00000040  // PLL Lock Raw Interrupt Status

/******************End of RCC Register configuration values**************/

/**
	* @brief Initialize General Purpose WTimer5 
	* @input  None
	* @retval None
  */

void WTimer5_Init(void);
/**
	* @brief Initialize General Purpose WTimer5 
	* @input  None
	* @retval Time in microseconds
  */

uint32_t getMicro(void);
/**
	* @brief Initialize General Purpose timer3A for periodic Interrupts
	* @input  None
	* @retval None
  */

void Timer3A_Init(void);

/**
	* @brief Initialize General Purpose timer2A for periodic Interrupts
	* @input  None
	* @retval None
  */

void Timer2A_Init(void);

/**
	* @brief Get ADC0 sample sequencer3 result
	* @input  None
	* @retval result
  */


 uint32_t ADC0_getResult(void);

 
void ADC0_Init(void);	

/**
	* @brief Configure System clock to run at 80Mhz
	* @input  None
	* @retval None
  */

void SystemClock_Config80Mhz(void);


/**
	*@brief  Generate milliseconds delay using general purpose timer
	*@input  Number of milliseconds delay
	*@retval None
 */
void DelayMs(uint32_t _time);


/**
  *@brief  Configure Cortex-M Systick Timer
	*@input  None
	*@retval None
	*/

void SystickConfig(void);



//Probe PORT = B
#define CH0					(1U<<0)  //Probe Channel 0 PIN
#define CH1					(1U<<1)  //Probe Channel 1 PIN
#define CH2					(1U<<2)  //Probe Channel 2 PIN
#define CH3					(1U<<3)  //Probe Channel 3 PIN


/**
  *@brief  Initialize 4 GPIOC pins as output
	*@input  None
	*@retval None
	*/
	
void Probe_Init(void);


/**
  *@brief  Toggle GPIOC_PIN_0
	*@input  None
	*@retval None
	*/
	
void Probe_CH0(void);

/**
  *@brief  Toggle GPIOC_PIN_1
	*@input  None
	*@retval None
	*/
void Probe_CH1(void);

/**
  *@brief  Toggle GPIOC_PIN_2
	*@input  None
	*@retval None
	*/

void Probe_CH2(void);

/**
  *@brief  Toggle GPIOC_PIN_3
	*@input  None
	*@retval None
	*/

void Probe_CH3(void);

/**
  *@brief  Initialize built-in LED pins on Port F
	*@input  LED Pin number in unsigned int
	*@retval None
	*/
	
void GPIOF_Init_LED(unsigned int LED);

/**
  *@brief  Toggle built-in RED LED pin on Port F
	*@input  None
	*@retval None
	*/
	
void BSP_LED_redToggle();

/**
  *@brief  Toggle built-in BLUE LED pin on Port F
	*@input  None
	*@retval None
	*/
	
void BSP_LED_blueToggle();

/**
  *@brief  Toggle built-in GREEN LED pin on Port F
	*@input  None
	*@retval None
	*/
	
void BSP_LED_greenToggle();

#endif

