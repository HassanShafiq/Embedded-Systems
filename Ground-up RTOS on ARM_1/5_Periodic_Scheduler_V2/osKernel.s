				AREA	|.text|, CODE, READONLY, ALIGN=2
				THUMB
				PRESERVE8
				EXTERN	currentPt	;importing currentPt pointer from osKernel.c
				EXPORT	SysTick_Handler
				EXPORT	osSchedulerLaunch
				IMPORT	osSchedulerRoundRobin
													

; This implementation of SysTick_Handler will perform the pre-emptive thread switch:
; SysTick is periodic interrupt and the period is equal to Quanta size, the argument that we passed to osKernelLaunch().

; Implementing Context save:
SysTick_Handler					; by-implementation saves R0, R1, R2, R3, R12, LR, PC, PSR
	CPSID		I	
	PUSH		{R4-R11}		; by-force saves R4-R11
	
	;The currentPt points to the Thread Control Block (TCB) of the currently running thread and has just exhuasted it's quanta 
	;and is in the process of being suspended for new thread to be loaded.
	LDR			R0, =currentPt	; R0 points to currentPt
	LDR			R1, [R0]		; R1 = currentPt
	STR     	SP, [R1]
	; Context saving completes here.		
	
	; Updating the Stack pointer to point to the top of stack of the new thread
	;LDR			R1, [R1, #4]	; R1 = currentPt->next
	;STR			R1, [R0]		; currentPt = R1
	PUSH		{R0, LR}
	BL			osSchedulerRoundRobin
	LDR			SP, [R1]		; SP = currentPt->stackPt
	
	POP			{R4-R11}
	CPSIE		I
	BX			LR
	
osSchedulerLaunch
	LDR			R0, =currentPt
	LDR			R2, [R0]		; R2 = currentPt
	LDR			SP, [R2]		; SP = currentPt->stackPt
	POP			{R4-R11}
	POP			{R0-R3}
	POP			{R12}
	ADD			SP, SP, #4
	POP			{LR}
	ADD 		SP, SP, #4
	CPSIE		I
	BX 			LR
	
	ALIGN
	END
