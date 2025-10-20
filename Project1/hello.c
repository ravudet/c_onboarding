#include <stdio.h>

void print(int x)
{
	printf("Integer:");
	printf(x);
	printf("\n");
}

/*void print(double x)
{
	printf("Double:");
	printf(x);
	printf("\n");
}*/

int main()
{
	print(5);
	print((int)3.14);
	return 0; 
}