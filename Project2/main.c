#include "main.h"

int main()
{
	char foo[] = "c:\\foo\\bar";
	getParentDirectory(foo, 9, "\\", 2);

	return 0;
}