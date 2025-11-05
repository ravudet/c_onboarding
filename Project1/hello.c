#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined _WIN32
#include <direct.h>
#elif defined __linux__
#include <sys/stat.h>
#endif

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

bool substrcmp(const char x[], const int xIndex, const char y[], const int yIndex, const int length)
{
	return memcmp(&x + xIndex, &y + yIndex, length) == 0;
}

int getParentDirectory(const char path[], const int endIndex, const char directoryDelimiter[], const int delimiterLength)
{
	int parentIndex = endIndex;
	if (substrcmp(path, endIndex - delimiterLength + 1, directoryDelimiter, 0, delimiterLength))
	{
		parentIndex = endIndex - delimiterLength + 1;
	}

	while (endIndex >= 0 && !substrcmp(path, endIndex - delimiterLength + 1, directoryDelimiter, 0, delimiterLength))
	{
		--parentIndex;
	}

	return parentIndex;
}

int mksubdir(const char path[], int endIndex)
{
	char* subPath = malloc(endIndex);
	if (subPath == NULL)
	{
		return errno;
	}

	memcpy(subPath, path, endIndex);

	int error = mkdir(subPath);
	return error;
}

int writeToFile(char path[], int pathLength, const char contents[])
{
	//// TODO separating the declaration from the initialization causes an error for some reason
	//// FILE* fptr;
	//// fptr = fopen(path, "a");

	FILE* fptr = fopen(path, "a");
	if (fptr == NULL)
	{
		int error = errno;
		if (error == 2)
		{
			int otherError = -1;
			int parentDirectoryEndIndex = pathLength - 1;
			while (otherError != 0)
			{
				char delimiter[] = "//";
				parentDirectoryEndIndex = getParentDirectory(path, parentDirectoryEndIndex, "//", sizeof(delimiter) / sizeof(delimiter[0]));
				otherError = mksubdir(path, parentDirectoryEndIndex);
			}

			//// TODO create the directory and then loop
		}

		return error; //// TODO i think this returns the pointer to the _errno function or something
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
}

int main()
{
	//// TODO make is so that you can use a path that doesn't exist
	//// TODO write a unit test to confirm that the file was written
	char path[] = "c:\\users\\ravud\\test\\test2\\test.txt";
	int error = writeToFile(path, sizeof(path) / sizeof(path[0]), "contents");
	if (error != 0)
	{
		printf("ERROR! %d", error); //// TODO https://learn.microsoft.com/en-us/cpp/c-runtime-library/errno-constants?view=msvc-170 or you can just look directly in `errno.h`
	}

	//// TODO https://stackoverflow.com/questions/13993742/is-there-any-way-to-peek-at-the-stdin-buffer
	int c = fgetc(stdin);

	return 0;
}