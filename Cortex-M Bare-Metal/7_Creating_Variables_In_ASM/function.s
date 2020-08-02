			AREA	DATA,ALIGN=2
amount		SPACE 	4
			EXPORT	amount
;------------------------------------------------
			AREA	|.text|,CODE,READONLY,ALIGN=2
			THUMB
			EXPORT	Amount_Func
Amount_Func
			LDR		R1, =amount
			MOV		R0, #89
			STR		R0, [R1]
			BX		LR
			ALIGN
			END