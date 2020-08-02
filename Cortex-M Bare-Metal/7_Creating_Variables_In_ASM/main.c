#include<stdint.h>

extern uint32_t	amount;
uint32_t	Amount_Func(void);
uint32_t	c_amount;

int main()
{
	Amount_Func();
	c_amount = amount;
}
