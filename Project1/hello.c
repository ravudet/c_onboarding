#include <errno.h>
#include <stdio.h>
#include <string.h>

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

// https://pubs.opengroup.org/onlinepubs/9699919799/functions/fclose.html

int writeToFile(const char path[], const char contents[])
{
	FILE* fptr = fopen(path, "a");
	if (fptr == NULL)
	{
		return errno; //// TODO i think this returns the pointer to the _errno function or something
	}

	int error = fprintf(fptr, contents);
	if (error < 0)
	{
		return errno;
	}

	error = fclose(fptr);
	if (error != 0)
	{
		return errno;
	}

	return 0;




	print(5);

	int a = 5;

	//// TODO write to a file, then write a unit test to confirm that the file was written
}

int main()
{
	int error = writeToFile("c:\\users\\ravud\\test.txt", "contents");
	if (error != 0)
	{
		printf("ERROR! %d", strerrorname_np());
	}

	return 0;
}