#include <stdio.h>
#include "pch.h"

void print2(int x)
{
	printf("Integer:");
	////printf(x);
	printf("\n");
}

/*void print2(double x)
{
	printf("Double:");
	printf("\n");
}*/

void CustomTest() {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(false);
}

/*int main()
{
	std::cout << "hello";
	CustomTest();
	return 0;
}*/