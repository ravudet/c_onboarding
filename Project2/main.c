#include "main.h"

int main()
{
	char foo[] = "asdf";
	char bar[] = "qwer";
	substrcmp(foo, 0, bar, 0, 4);

	substring(foo, 0, &bar);

	return 0;
}