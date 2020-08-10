// SVC (Supervisor Call) Exceptions;
// Generic Format to write the prototype for an SVC Instruction:
// [return type] __svc([svc exception number]) [svc service name]([arguments list along with data types]);
// This prototyping is working exactly like it would do for #define statements for symbolic constants:
int __svc(0x00) svc_service_add(int x, int y);
int __svc(0x01) svc_service_sub(int x, int y);
int __svc(0x02) svc_service_mul(int x, int y);
int __svc(0x03) svc_service_div(int x, int y);

void SVC_Handler_C(unsigned int * svc_args);

int x, y, z;

int main ()
{
		x = 1;
		y = 5;
		z = svc_service_add(x, y);
	
		x = 9;
		y = 5;
		z = svc_service_sub(x, y);
	
		x = 5;
		y = 5;
		z = svc_service_mul(x, y);
	
		x = 10;
		y = 5;
		z = svc_service_div(x, y);
}

__asm void SVC_Handler(void)
{
	// Step #1: Test Link Registe bit #2, counting from 0, to know the stack used by the processor (MSP/PSP) as it contains the EXC_RETURN value in it.
	TST LR, #4 //0b 0100
	ITE EQ
	MRSEQ R0, MSP
	MRSNE	R0, PSP
	B				__cpp(SVC_Handler_C)
}

void SVC_Handler_C(unsigned int * svc_args) // Pointer to svc_args represents pointer to stack frame upon SVC exception, that has access to it.
{
	unsigned int svc_number;
	svc_number = ((char *)svc_args[6])[-2]; // [-2] to get the first byte of the svc instruction, which represents the SVC number.
	
	switch(svc_number)
	{
		case 0:
			svc_args[0] = svc_args[0] + svc_args[1]; // Using these registers as per AAPCS. R0 = R0 + R1. RO and R1 are parameters passing registers and R0 as return value register.
			break;
		case 1:
			svc_args[0] = svc_args[0] - svc_args[1]; // Using these registers as per AAPCS. R0 = R0 + R1. RO and R1 are parameters passing registers and R0 as return value register.
			break;
		case 2:
			svc_args[0] = svc_args[0] * svc_args[1]; // Using these registers as per AAPCS. R0 = R0 + R1. RO and R1 are parameters passing registers and R0 as return value register.
			break;
		case 3:
			svc_args[0] = svc_args[0] / svc_args[1]; // Using these registers as per AAPCS. R0 = R0 + R1. RO and R1 are parameters passing registers and R0 as return value register.
			break;
		default:
			break;
	}
	
}
