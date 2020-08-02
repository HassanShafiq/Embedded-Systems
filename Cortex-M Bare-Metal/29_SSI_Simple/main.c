#include "TM4C123.h"                    // Device header

void SSI_Init(void);
void SSIWrite (unsigned char data);

int main (void)
{
	SSI_Init();
	unsigned char i;
	
	while (1)
	{
		for(i = 'A' ; i <= 'Z' ; i++)
		{
			SSIWrite(i);
		}
	}
}

void SSI_Init(void)
{
	SYSCTL->RCGCSSI		|=	0x02;					//Enabling RCGC for SSI_1
	SYSCTL->RCGCGPIO	|=	0x08;					//Enabling RCGC for Port_D
	SYSCTL->RCGCGPIO	|=	0x20;					//Enabling RCGC for Port_F
	
	GPIOD->AMSEL			&= 	~0x09;				//Disabling analog for PD0, PD3
	GPIOD->DEN				|=	0x09;					//Digital Enable for PD0, PD3
	GPIOD->AFSEL			|=	0x09;					//Enabling Alternatre Function Select for PD0, PD1
	GPIOD->PCTL				&=	~0x0000F00F;	//PortMuxControl Encoding
	
	GPIOF->DEN				|=	0x04;					//Digital enable for PF2
	GPIOF->DIR				|=	0x04;					//To be used as Slave Assert Pin
	GPIOF->DATA				|=	0x04;					//
	
	// Configuring SSI as:
	// Master, POL = 0, PHA = 0, Clock = 4 MHz, 16 Bit Data Transfer.
	SSI1->CR1					=		0x00;
	SSI1->CC					= 	0x00;
	SSI1->CPSR				= 	0x02;					//Prescale divided by 2
	SSI1->CR0					= 	0x0007;				//8 MHz SSI Clock, SPI Mode, 8 bit data
	SSI1->CR1					|=	0x02;					//SSI Enable
}

void SSIWrite (unsigned char data)
{
	GPIOF->DATA				&=	~0x04;				//Disabling Slave Assert Pin
	
	while((SSI1->SR & 0x02) == 0x00){} 	//Pool to check if the transmit FIFO is empty
	SSI1->DR					= 	data;
	
	while(SSI1->SR & 0x10){}						//Pool to check if the data tranmission is complete
	GPIOF->DATA				|=	0x04;					//Enabling Slave Assert Pin
}