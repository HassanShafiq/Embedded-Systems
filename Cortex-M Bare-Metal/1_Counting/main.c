int number = 0;
int *ptr;

int main ()
{
	ptr = &number;
	while(1)
	{
		while(*ptr <8)
		{
			++*ptr;
			if (*ptr == 8)
			{
				*ptr = 0;
				break;
			}
		}
		
		ptr =(int *)0x20000014U;
		*ptr = 0x0000BEEF;
	}
}	
