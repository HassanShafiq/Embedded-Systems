#include "delay.h"

extern void call_delay(uint32_t seconds)
{
	int delay = 0;
	for (int i = 0; i < seconds ; i++)
	{
		while (delay < 1000000)
		{
			delay++;
		}
		delay = 0;
	}
}

