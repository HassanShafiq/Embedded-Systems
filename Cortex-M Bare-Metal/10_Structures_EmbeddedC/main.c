#include<stdint.h>
/*
// Declaration Style 1:
struct Boy{
	uint8_t		age;
	uint8_t		height;
}boy1, boy2;
*/

/*
// Declaration Style 2:
struct {
	uint8_t 	age;
	uint8_t		height;
}boy1, boy2;
*/

/*
// Declaration Syle 3:
struct Boy{
	uint8_t		age;
	uint8_t		height;
};
//struct	Boy boy1, boy2;
typedef struct Boy Boy;
Boy	boy1;
Boy	boy2;
*/

typedef struct{
	uint8_t		age;
	uint8_t		height;
}Boy;

// Nesting Structures through declaring a structure member as type of another structe and so on:
typedef struct{
	Boy		error[2];
}Precision;

Boy 				Babar, Brendon;
Precision		precision;
	
// Using typedef to come around the excessive usage of Struct keyword:
int main ()
{
	Babar.age = 26;
	Babar.height = 6;
	
	Brendon.age = 38;
	Brendon.height = 6;
	
	precision.error[0].age = 1;
	precision.error[1].age = 2;
}

