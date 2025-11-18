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
	for (int i = 0; i < length; ++i)
	{
		char xValue = x[xIndex + i];
		char yValue = y[yIndex + i];
		if (xValue != yValue)
		{
			return false;
		}
	}

	return true;
	//// TODO use this line instead: return memcmp(&x + xIndex, &y + yIndex, length) == 0;
}

int getParentDirectory(const char path[], const int endIndex, const char directoryDelimiter[], const int delimiterLength)
{
	int parentIndex = endIndex;
	if (substrcmp(path, parentIndex - delimiterLength, directoryDelimiter, 0, delimiterLength))
	{
		parentIndex = parentIndex - delimiterLength;
	}

	while (parentIndex >= 0 && !substrcmp(path, parentIndex - delimiterLength, directoryDelimiter, 0, delimiterLength))
	{
		--parentIndex;
	}

	return parentIndex;
}

const int SUCCESS = 0;
const int UNDEFINED = -1;

enum mksubdirError
{
	mksubdirError_BUG = 1,
	mksubdirError_EACCES,
	mksubdirError_EEXIST,
	mksubdirError_ELOOP,
	mksubdirError_EMLINK,
	mksubdirError_ENAMETOOLONG,
	mksubdirError_ENOENT,
	mksubdirError_ENOSPC,
	mksubdirError_ENOTDIR,
	mksubdirError_EROFS,
	mksubdirError_ENOMEM,
};

enum mksubdirError mksubdir(const char path[], const int endIndex)
{
	enum mksubdirError returnValue = SUCCESS;

	char* subPath = malloc(endIndex + 1);
	if (subPath == NULL)
	{
		int error = errno;
		switch (error)
		{
			case ENOMEM:
				returnValue = mksubdirError_ENOMEM;
				break;
			default:
				returnValue = mksubdirError_BUG;
				break;
		}

		goto finally;
	}

	subPath[endIndex] = '\0';
	memcpy(subPath, path, endIndex);

	int error = mkdir(subPath);
	if (error == -1)
	{
		error = errno;
		switch (error)
		{
			case EACCES:
				returnValue = mksubdirError_EACCES;
				break;
			case EEXIST:
				returnValue = mksubdirError_EEXIST;
				break;
			case ELOOP:
				returnValue = mksubdirError_ELOOP;
				break;
			case EMLINK:
				returnValue = mksubdirError_EMLINK;
				break;
			case ENAMETOOLONG:
				returnValue = mksubdirError_ENAMETOOLONG;
				break;
			case ENOENT:
				returnValue = mksubdirError_ENOENT;
				break;
			case ENOSPC:
				returnValue = mksubdirError_ENOSPC;
				break;
			case ENOTDIR:
				returnValue = mksubdirError_ENOTDIR;
				break;
			case EROFS:
				returnValue = mksubdirError_EROFS;
				break;
			default:
				returnValue = mksubdirError_BUG;
				break;
		}

		goto finally;
	}

finally:
	free(subPath);
	return returnValue;
}

enum mkdirectorytraversalError
{
	mkdirectorytraversalError_BUG = 1,
	mkdirectorytraversalError_EACCES,
	mkdirectorytraversalError_ELOOP,
	mkdirectorytraversalError_EMLINK,
	mkdirectorytraversalError_ENAMETOOLONG,
	mkdirectorytraversalError_ENOSPC,
	mkdirectorytraversalError_ENOTDIR,
	mkdirectorytraversalError_EROFS,
	mkdirectorytraversalError_ENOMEM,
};

enum mkdirectorytraversalError mkdirectorytraversal(const char directoryPath[], int pathLength)
{
	char delimiter[] = "\\";
	enum mkdirectorytraversalError returnValue = SUCCESS;

	enum mksubdirError error = mksubdirError_ENOENT;
	int parentDirectoryEndIndex = pathLength - 1;
	while (error == mksubdirError_ENOENT)
	{
		error = mksubdir(directoryPath, parentDirectoryEndIndex);
		if (error != SUCCESS)
		{
			switch (error)
			{
				case mksubdirError_EACCES:
					returnValue = mkdirectorytraversalError_EACCES;
					break;
				case mksubdirError_EEXIST:
					break;
				case mksubdirError_ELOOP:
					returnValue = mkdirectorytraversalError_ELOOP;
					break;
				case mksubdirError_EMLINK:
					returnValue = mkdirectorytraversalError_EMLINK;
					break;
				case mksubdirError_ENAMETOOLONG:
					returnValue = mkdirectorytraversalError_ENAMETOOLONG;
					break;
				case mksubdirError_ENOENT:
					parentDirectoryEndIndex = getParentDirectory(directoryPath, parentDirectoryEndIndex, delimiter, (sizeof(delimiter) / sizeof(delimiter[0])) - 1);
					mkdirectorytraversal(directoryPath, parentDirectoryEndIndex);
					continue;
				case mksubdirError_ENOMEM:
					returnValue = mkdirectorytraversalError_ENOMEM;
					break;
				case mksubdirError_ENOSPC:
					returnValue = mkdirectorytraversalError_ENOSPC;
					break;
				case mksubdirError_ENOTDIR:
					returnValue = mkdirectorytraversalError_ENOTDIR;
					break;
				case mksubdirError_EROFS:
					returnValue = mkdirectorytraversalError_EROFS;
					break;
				default:
					returnValue = mkdirectorytraversalError_BUG;
					break;
			}

			goto finally;
		}
	}

finally:
	return returnValue;
}

//// TODO sqllite c repo so that you can get good practices?

int writeToFile(const char path[], int pathLength, const char contents[])
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

int writeToFilePath(const char path[], int pathLength, const char contents[])
{
	int error = writeToFile(path, pathLength, contents);
	if (error == 2)
	{
		mkdirectorytraversal(path, pathLength);
	}
}

int main()
{
	//// TODO make is so that you can use a path that doesn't exist
	//// TODO write a unit test to confirm that the file was written
	char path[] = "c:\\users\\ravud\\test\\test2\\test.txt";
	mkdirectorytraversal(path, sizeof(path) / sizeof(path[0]));

	int error = writeToFile(path, sizeof(path) / sizeof(path[0]), "contents");
	if (error != 0)
	{
		printf("ERROR! %d", error); //// TODO https://learn.microsoft.com/en-us/cpp/c-runtime-library/errno-constants?view=msvc-170 or you can just look directly in `errno.h`
	}

	//// TODO https://stackoverflow.com/questions/13993742/is-there-any-way-to-peek-at-the-stdin-buffer
	int c = fgetc(stdin);

	return 0;
}