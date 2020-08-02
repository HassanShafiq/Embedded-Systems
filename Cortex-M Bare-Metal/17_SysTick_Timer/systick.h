#ifndef __SYSTICK_H__
#define	__SYSTICK_H__

#include <stdbool.h>

#define		ONESEC	(16000000 - 1)
#define		ENMOSC	0x05
#define		CLEAR_R	0x00

bool Timeout(void);
void SysTick_Init(void);

#endif