#include<stdint.h>

uint32_t Number(void);
uint32_t value;
uint32_t ans;

int main()
{
	value = Number();
	ans = (value + 230) * 2;
}
