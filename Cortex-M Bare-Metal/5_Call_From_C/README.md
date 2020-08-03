This exercise implements a piece of embedded functionality (routine) in Cortex-M assembly language in a .s file instead of a .c file and then calls it inside the .c file (main.c here).

This technique greatly improves the program execution speed as it allows using **compiler intrinsics** as well apart from the liberty for to use assembly commands directly and is implemented in embedded software routines, requiring higher execution efficiency.
