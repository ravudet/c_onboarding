#include "main.h"

int main()
{
	char foo[] = "c:\\foo\\bar";
	getParentDirectory(foo, 9, "\\", 2);

	mksubdir(foo, 7);

	return 0;
}