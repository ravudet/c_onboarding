#include <errno.h>
#include <stdarg.h>
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

const int SUCCESS = 0;
const int UNDEFINED = -1;

enum substringError
{
	substringError_BUG = 1,
	substringError_ENOMEM,
};

//// TODO can you have a macro or something to tell the compiler that `substring` is not null if `0` is returned?
enum substringError substring(const char string[], const int endIndex, char* substringPointer[])
{
	enum substringError returnValue = SUCCESS;

	char* substring = malloc(endIndex + 1);
	if (substring == NULL)
	{
		int error = errno;
		switch (error)
		{
			case ENOMEM:
				returnValue = substringError_ENOMEM;
				break;
			default:
				returnValue = substringError_BUG;
				break;
		}

		goto catch;
	}

	substring[endIndex] = '\0';
	memcpy(substring, string, endIndex);

	*substringPointer = substring;
	goto finally;

catch:
	free(substring);

finally:
	return returnValue;
}

bool substrcmp(const char x[], const int xStart, const char y[], const int yStart, const int length)
{
	return memcmp(x + xStart, y + yStart, length) == 0;
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

enum ravudetmkdirError
{
	ravudetmkdirError_BUG = 1,
	ravudetmkdirError_NULLPOINTER,
	ravudetmkdirError_EACCES,
	ravudetmkdirError_EEXIST,
	ravudetmkdirError_ELOOP,
	ravudetmkdirError_EMLINK,
	ravudetmkdirError_ENAMETOOLONG,
	ravudetmkdirError_ENOENT,
	ravudetmkdirError_ENOSPC,
	ravudetmkdirError_ENOTDIR,
	ravudetmkdirError_EROFS,
};

enum ravudetmkdirError ravudetmkdir(const char path[])
{
	enum ravudetmkdirError returnValue = SUCCESS;
	
	if (path == NULL)
	{
		returnValue = ravudetmkdirError_NULLPOINTER;
		goto finally;
	}

	int mkdirError = mkdir(path);
	if (mkdirError == -1)
	{
		mkdirError = errno;
		switch (mkdirError)
		{
		case EACCES:
			returnValue = ravudetmkdirError_EACCES;
			break;
		case EEXIST:
			returnValue = ravudetmkdirError_EEXIST;
			break;
		case ELOOP:
			returnValue = ravudetmkdirError_ELOOP;
			break;
		case EMLINK:
			returnValue = ravudetmkdirError_EMLINK;
			break;
		case ENAMETOOLONG:
			returnValue = ravudetmkdirError_ENAMETOOLONG;
			break;
		case ENOENT:
			returnValue = ravudetmkdirError_ENOENT;
			break;
		case ENOSPC:
			returnValue = ravudetmkdirError_ENOSPC;
			break;
		case ENOTDIR:
			returnValue = ravudetmkdirError_ENOTDIR;
			break;
		case EROFS:
			returnValue = ravudetmkdirError_EROFS;
			break;
		default:
			returnValue = ravudetmkdirError_BUG;
			break;
		}

		goto finally;
	}

finally:
	return returnValue;
}

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
	int error;

	char* subPath;
	error = substring(path, endIndex, &subPath);
	if (error != SUCCESS)
	{
		switch (error)
		{
			case substringError_ENOMEM:
				returnValue = mksubdirError_ENOMEM;
				break;
			default:
				returnValue = mksubdirError_BUG;
				break;
		}

		goto finally;
	}

	error = ravudetmkdir(subPath);
	if (error != SUCCESS)
	{
		switch (error)
		{
			case ravudetmkdirError_EACCES:
				returnValue = mksubdirError_EACCES;
				break;
			case ravudetmkdirError_EEXIST:
				returnValue = mksubdirError_EEXIST;
				break;
			case ravudetmkdirError_ELOOP:
				returnValue = mksubdirError_ELOOP;
				break;
			case ravudetmkdirError_EMLINK:
				returnValue = mksubdirError_EMLINK;
				break;
			case ravudetmkdirError_ENAMETOOLONG:
				returnValue = mksubdirError_ENAMETOOLONG;
				break;
			case ravudetmkdirError_ENOENT:
				returnValue = mksubdirError_ENOENT;
				break;
			case ravudetmkdirError_ENOSPC:
				returnValue = mksubdirError_ENOSPC;
				break;
			case ravudetmkdirError_ENOTDIR:
				returnValue = mksubdirError_ENOTDIR;
				break;
			case ravudetmkdirError_EROFS:
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
	const char delimiter[] = "\\";

	enum mkdirectorytraversalError returnValue = SUCCESS;
	int error;

	int parentDirectoryEndIndex;
	error = mksubdirError_ENOENT;
	while (error == mksubdirError_ENOENT)
	{
		error = mksubdir(directoryPath, pathLength - 1);
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
					parentDirectoryEndIndex = getParentDirectory(directoryPath, pathLength - 1, delimiter, (sizeof(delimiter) / sizeof(delimiter[0])) - 1);
					returnValue = mkdirectorytraversal(directoryPath, parentDirectoryEndIndex);
					if (returnValue == SUCCESS)
					{
						continue;
					}
					else
					{
						break;
					}
				case mksubdirError_ENOSPC:
					returnValue = mkdirectorytraversalError_ENOSPC;
					break;
				case mksubdirError_ENOTDIR:
					returnValue = mkdirectorytraversalError_ENOTDIR;
					break;
				case mksubdirError_EROFS:
					returnValue = mkdirectorytraversalError_EROFS;
					break;
				case mksubdirError_ENOMEM:
					returnValue = mkdirectorytraversalError_ENOMEM;
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

enum ravudetfopenError
{
	ravudetfopenError_BUG = 1,
	ravudetfopenError_EACCES,
	ravudetfopenError_EINTR,
	ravudetfopenError_EISDIR,
	ravudetfopenError_ELOOP,
	ravudetfopenError_EMFILE,
	ravudetfopenError_ENAMETOOLONG,
	ravudetfopenError_ENFILE,
	ravudetfopenError_ENOENT,
	ravudetfopenError_ENOSPC,
	ravudetfopenError_ENOTDIR,
	ravudetfopenError_ENXIO,
	ravudetfopenError_EOVERFLOW,
	ravudetfopenError_EROFS,
	ravudetfopenError_EINVAL,
	ravudetfopenError_ENOMEM,
	ravudetfopenError_ETXTBSY,
};

enum ravudetfopenError ravudetfopen(const char filePath[], const char* mode, const FILE** fileHandle)
{
	enum ravudetfopenError returnValue = SUCCESS;

#pragma warning(suppress : 4996) // we are preferring portability over supposed "security"
	*fileHandle = fopen(filePath, mode);

	if (fileHandle == NULL)
	{
		int fopenError = errno;
		switch (fopenError)
		{
			case EACCES:
				returnValue = ravudetfopenError_EACCES;
				break;
			case EINTR:
				returnValue = ravudetfopenError_EINTR;
				break;
			case EISDIR:
				returnValue = ravudetfopenError_EISDIR;
				break;
			case ELOOP:
				returnValue = ravudetfopenError_ELOOP;
				break;
			case EMFILE:
				returnValue = ravudetfopenError_EMFILE;
				break;
			case ENAMETOOLONG:
				returnValue = ravudetfopenError_ENAMETOOLONG;
				break;
			case ENFILE:
				returnValue = ravudetfopenError_ENFILE;
				break;
			case ENOENT:
				returnValue = ravudetfopenError_ENOENT;
				break;
			case ENOSPC:
				returnValue = ravudetfopenError_ENOSPC;
				break;
			case ENOTDIR:
				returnValue = ravudetfopenError_ENOTDIR;
				break;
			case ENXIO:
				returnValue = ravudetfopenError_ENXIO;
				break;
			case EOVERFLOW:
				returnValue = ravudetfopenError_EOVERFLOW;
				break;
			case EROFS:
				returnValue = ravudetfopenError_EROFS;
				break;
			case EINVAL:
				returnValue = ravudetfopenError_EINVAL;
				break;
			case ENOMEM:
				returnValue = ravudetfopenError_ENOMEM;
				break;
			case ETXTBSY:
				returnValue = ravudetfopenError_ETXTBSY;
				break;
			default:
				returnValue = ravudetfopenError_BUG;
				break;
		}

		goto finally;
	}

finally:
	return returnValue;
}

enum ravudetfprintfError
{
	ravudetfprintfError_BUG = 1,
	ravudetfprintfError_EAGAIN,
	ravudetfprintfError_EBADF,
	ravudetfprintfError_EFBIG,
	ravudetfprintfError_EINTR,
	ravudetfprintfError_EIO,
	ravudetfprintfError_ENOSPC,
	ravudetfprintfError_EPIPE,
	ravudetfprintfError_ENOMEM,
	ravudetfprintfError_ENXIO,
	ravudetfprintfError_EILSEQ,
	ravudetfprintfError_EOVERFLOW,
};

enum ravudetfprintfError ravudetfprintf(FILE* stream, int* bytesWritten, const char* format, ...)
{
	enum ravudetfprintfError returnValue = SUCCESS;

	va_list vl;
	va_start(vl, format);

	int error = vfprintf(stream, format, vl);
	if (error < 0)
	{
		switch (error)
		{
			case EAGAIN:
				returnValue = ravudetfprintfError_EAGAIN;
				break;
			case EBADF:
				returnValue = ravudetfprintfError_EBADF;
				break;
			case EFBIG:
				returnValue = ravudetfprintfError_EFBIG;
				break;
			case EINTR:
				returnValue = ravudetfprintfError_EINTR;
				break;
			case EIO:
				returnValue = ravudetfprintfError_EIO;
				break;
			case ENOSPC:
				returnValue = ravudetfprintfError_ENOSPC;
				break;
			case EPIPE:
				returnValue = ravudetfprintfError_EPIPE;
				break;
			case ENOMEM:
				returnValue = ravudetfprintfError_ENOMEM;
				break;
			case ENXIO:
				returnValue = ravudetfprintfError_ENXIO;
				break;
			case EILSEQ:
				returnValue = ravudetfprintfError_EILSEQ;
				break;
			case EOVERFLOW:
				returnValue = ravudetfprintfError_EOVERFLOW;
			default:
				returnValue = ravudetfprintfError_BUG;
		}

		goto finally;
	}

	*bytesWritten = error;

finally:
	return returnValue;
}

enum writeToFileError
{
	writeToFileError_BUG = 1,
	writeToFileError_EACCES,
	writeToFileError_EINTR,
	writeToFileError_EISDIR,
	writeToFileError_ELOOP,
	writeToFileError_EMFILE,
	writeToFileError_ENAMETOOLONG,
	writeToFileError_ENFILE,
	writeToFileError_ENOENT,
	writeToFileError_ENOSPC,
	writeToFileError_ENOTDIR,
	writeToFileError_ENXIO,
	writeToFileError_EOVERFLOW,
	writeToFileError_EROFS,
	writeToFileError_EINVAL,
	writeToFileError_ENOMEM,
	writeToFileError_ETXTBSY,
};

enum writeToFileError writeToFile(const char filePath[], int pathLength, const char contents[])
{
	enum writeToFileError returnValue = SUCCESS;
	int error;

	FILE* fptr;
	error = ravudetfopen(filePath, "a", &fptr);
	if (error != SUCCESS)
	{
		switch (error)
		{
			case ravudetfopenError_EACCES:
				returnValue = writeToFileError_EACCES;
				break;
			case ravudetfopenError_EINTR:
				returnValue = writeToFileError_EINTR;
				break;
			case ravudetfopenError_EISDIR:
				returnValue = writeToFileError_EISDIR;
				break;
			case ravudetfopenError_ELOOP:
				returnValue = writeToFileError_ELOOP;
				break;
			case ravudetfopenError_EMFILE:
				returnValue = writeToFileError_EMFILE;
				break;
			case ravudetfopenError_ENAMETOOLONG:
				returnValue = writeToFileError_ENAMETOOLONG;
				break;
			case ravudetfopenError_ENFILE:
				returnValue = writeToFileError_ENFILE;
				break;
			case ravudetfopenError_ENOENT:
				returnValue = writeToFileError_ENOENT;
				break;
			case ravudetfopenError_ENOSPC:
				returnValue = writeToFileError_ENOSPC;
				break;
			case ravudetfopenError_ENOTDIR:
				returnValue = writeToFileError_ENOTDIR;
				break;
			case ravudetfopenError_ENXIO:
				returnValue = writeToFileError_ENXIO;
				break;
			case ravudetfopenError_EOVERFLOW:
				returnValue = writeToFileError_EOVERFLOW;
				break;
			case ravudetfopenError_EROFS:
				returnValue = writeToFileError_EROFS;
				break;
			case ravudetfopenError_EINVAL:
				returnValue = writeToFileError_EINVAL;
				break;
			case ravudetfopenError_ENOMEM:
				returnValue = writeToFileError_ENOMEM;
				break;
			case ravudetfopenError_ETXTBSY:
				returnValue = writeToFileError_ETXTBSY;
				break;
			default:
				returnValue = writeToFileError_BUG;
				break;

		}

		goto finally;
	}



	//// TODO you are here
	//// TODO follow the same error handling pattern as the above 2 methods
	int bytesWritten;
	error = ravudetfprintf(fptr, &bytesWritten, contents);
	if (error != SUCCESS)
	{
		switch (error)
		{
			default:
				returnValue = writeToFileError_BUG;
		}

		goto finally;
	}

	error = fclose(fptr);
	if (error != 0)
	{
		return errno;
	}

finally:
	return returnValue;
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
	char path[] = "c:\\users\\ravud\\test\\test2\\";
	mkdirectorytraversal(path, sizeof(path) / sizeof(path[0]));

	char path2[] = "c:\\users\\ravud\\test\\test2\\test.txt";
	int error = writeToFile(path2, sizeof(path2) / sizeof(path2[0]), "contents");
	if (error != 0)
	{
		printf("ERROR! %d", error); //// TODO https://learn.microsoft.com/en-us/cpp/c-runtime-library/errno-constants?view=msvc-170 or you can just look directly in `errno.h`
	}

	//// TODO https://stackoverflow.com/questions/13993742/is-there-any-way-to-peek-at-the-stdin-buffer
	int c = fgetc(stdin);

	return 0;
}