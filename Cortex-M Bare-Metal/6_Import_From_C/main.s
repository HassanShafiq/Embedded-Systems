				AREA		DATA, ALIGN=2
				IMPORT 		number
				IMPORT 		Adder
				AREA		|.text|,CODE,READONLY,ALIGN=2
				THUMB
				EXPORT		Main
Main
				LDR		R1, =number
				MOV		R0, #100
				STR		R0, [R1]
				BL		Adder
				ALIGN
				END