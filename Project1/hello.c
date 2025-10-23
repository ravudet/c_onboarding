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

void writeToFile(char path[], char contents[])
{
	int pathLength = sizeof(path) / sizeof(path[0]);
	//// TODO write to a file, then write a unit test to confirm that the file was written
}

int main()
{
	print(5);
	print((int)3.14);
	return 0; 
}