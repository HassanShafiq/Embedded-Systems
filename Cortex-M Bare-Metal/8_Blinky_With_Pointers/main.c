/*
#include<stdint.h>
#include<tm4c123gh6pm.h>
int main ()
{
	unsigned int *ptr;
	
	// Initializing Clock Gating Control Register:
	ptr = (unsigned int *) 0x400FE608U;
	*ptr = 0x20U;
	
	// Initializing Direction Register for PortF as output for PF3-1:
	ptr = (unsigned int *) 0x40025400U;
	*ptr = 0x0EU;
	
	// Initializing Digital Enable Register for PF3-1:
	ptr = (unsigned int *) 0x4002551CU;
	*ptr = 0x0EU;
	
	// Writing Output in DATA Register for PF3-1:
	ptr = (unsigned int *) 0x400253FCU;
	*ptr = 0x0EU;
}

*/