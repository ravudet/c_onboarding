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
		int error = errno;
		switch (error)
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
		int error = errno;
		switch (error)
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

	int potentialBytesWritten = vfprintf(stream, format, vl);
	if (potentialBytesWritten < 0)
	{
		int error = errno;
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
				break;
			default:
				returnValue = ravudetfprintfError_BUG;
				break;
		}

		goto finally;
	}

	*bytesWritten = potentialBytesWritten;

finally:
	return returnValue;
}

enum ravudetfcloseError
{
	ravudetfcloseError_BUG = 1,
	ravudetfcloseError_EAGAIN,
	ravudetfcloseError_EBADF,
	ravudetfcloseError_EFBIG,
	ravudetfcloseError_EINTR,
	ravudetfcloseError_EIO,
	ravudetfcloseError_ENOMEM,
	ravudetfcloseError_ENOSPC,
	ravudetfcloseError_EPIPE,
	ravudetfcloseError_ENXIO,
};

enum ravudetfcloseError ravudetfclose(FILE* stream)
{
	enum ravudetfcloseError returnValue = SUCCESS;

	int fcloseError = fclose(stream);
	if (fcloseError != 0)
	{
		int error = errno;
		switch (error)
		{
			case EAGAIN:
				returnValue = ravudetfcloseError_EAGAIN;
				break;
			case EBADF:
				returnValue = ravudetfcloseError_EBADF;
				break;
			case EFBIG:
				returnValue = ravudetfcloseError_EFBIG;
				break;
			case EINTR:
				returnValue = ravudetfcloseError_EINTR;
				break;
			case EIO:
				returnValue = ravudetfcloseError_EIO;
				break;
			case ENOMEM:
				returnValue = ravudetfcloseError_ENOMEM;
				break;
			case ENOSPC:
				returnValue = ravudetfcloseError_ENOSPC;
				break;
			case EPIPE:
				returnValue = ravudetfcloseError_EPIPE;
				break;
			case ENXIO:
				returnValue = ravudetfcloseError_ENXIO;
				break;
			default:
				returnValue = ravudetfcloseError_BUG;
				break;
		}
		
		goto finally;
	}

finally:
	return returnValue;
}

enum writeToFileError
{
	writeToFileError_BUG = 1,
	writeToFileError_EACCES,
	writeToFileError_OPEN_EINTR,
	writeToFileError_EISDIR,
	writeToFileError_ELOOP,
	writeToFileError_EMFILE,
	writeToFileError_ENAMETOOLONG,
	writeToFileError_ENFILE,
	writeToFileError_ENOENT,
	writeToFileError_ENOSPC,
	writeToFileError_ENOTDIR,
	writeToFileError_ENXIO,
	writeToFileError_OPEN_EOVERFLOW,
	writeToFileError_EROFS,
	writeToFileError_EINVAL,
	writeToFileError_ENOMEM,
	writeToFileError_ETXTBSY,
	writeToFileError_EAGAIN,
	writeToFileError_EFBIG,
	writeToFileError_PRINT_EINTR,
	writeToFileError_EIO,
	writeToFileError_EPIPE,
	writeToFileError_EILSEQ,
	writeToFileError_PRINT_EOVERFLOW,
	writeToFileError_CLOSE_EAGAIN,
	writeToFileError_CLOSE_EFBIG,
	writeToFileError_CLOSE_EINTR,
	writeToFileError_CLOSE_EIO,
	writeToFileError_CLOSE_ENOMEM,
	writeToFileError_CLOSE_ENOSPC,
	writeToFileError_CLOSE_EPIPE,
	writeToFileError_CLOSE_ENXIO,
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
				returnValue = writeToFileError_OPEN_EINTR;
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
				returnValue = writeToFileError_OPEN_EOVERFLOW;
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

	int bytesWritten;
	error = ravudetfprintf(fptr, &bytesWritten, contents);
	if (error != SUCCESS)
	{
		switch (error)
		{
			case ravudetfprintfError_EAGAIN:
				returnValue = writeToFileError_EAGAIN;
				break;
			case ravudetfprintfError_EFBIG:
				returnValue = writeToFileError_EFBIG;
				break;
			case ravudetfprintfError_EINTR:
				returnValue = writeToFileError_PRINT_EINTR;
				break;
			case ravudetfprintfError_EIO:
				returnValue = writeToFileError_EIO;
				break;
			case ravudetfprintfError_ENOSPC:
				returnValue = writeToFileError_ENOSPC;
				break;
			case ravudetfprintfError_EPIPE:
				returnValue = writeToFileError_EPIPE;
				break;
			case ravudetfprintfError_ENOMEM:
				returnValue = writeToFileError_ENOMEM;
				break;
			case ravudetfprintfError_ENXIO:
				returnValue = writeToFileError_ENXIO;
				break;
			case ravudetfprintfError_EILSEQ:
				returnValue = writeToFileError_EILSEQ;
				break;
			case ravudetfprintfError_EOVERFLOW:
				returnValue = writeToFileError_PRINT_EOVERFLOW;
				break;
			default:
				returnValue = writeToFileError_BUG;
				break;
		}

		goto finally;
	}

	error = ravudetfclose(fptr);
	if (error != SUCCESS)
	{
		switch (error)
		{
			case ravudetfcloseError_EAGAIN:
				returnValue = writeToFileError_CLOSE_EAGAIN;
				break;
			case ravudetfcloseError_EFBIG:
				returnValue = writeToFileError_CLOSE_EFBIG;
				break;
			case ravudetfcloseError_EINTR:
				returnValue = writeToFileError_CLOSE_EINTR;
				break;
			case ravudetfcloseError_EIO:
				returnValue = writeToFileError_CLOSE_EIO;
				break;
			case ravudetfcloseError_ENOMEM:
				returnValue = writeToFileError_CLOSE_ENOMEM;
				break;
			case ravudetfcloseError_ENOSPC:
				returnValue = writeToFileError_CLOSE_ENOSPC;
				break;
			case ravudetfcloseError_EPIPE:
				returnValue = writeToFileError_CLOSE_EPIPE;
				break;
			case ravudetfcloseError_ENXIO:
				returnValue = writeToFileError_CLOSE_ENXIO;
				break;
			default:
				returnValue = writeToFileError_BUG;
				break;
		}

		//// TODO what can my caller do if there's a failure to close the file?
		goto finally;
	}

finally:
	return returnValue;
}

enum writeToFilePathError
{
	writeToFilePathError_BUG = 1,
	writeToFilePathError_EACCES,
	writeToFilePathError_OPEN_EINTR,
	writeToFilePathError_EISDIR,
	writeToFilePathError_ELOOP,
	writeToFilePathError_EMFILE,
	writeToFilePathError_ENAMETOOLONG,
	writeToFilePathError_ENFILE,
	writeToFilePathError_ENOENT,
	writeToFilePathError_ENOSPC,
	writeToFilePathError_ENOTDIR,
	writeToFilePathError_ENXIO,
	writeToFilePathError_OPEN_EOVERFLOW,
	writeToFilePathError_EROFS,
	writeToFilePathError_EINVAL,
	writeToFilePathError_ENOMEM,
	writeToFilePathError_ETXTBSY,
	writeToFilePathError_EAGAIN,
	writeToFilePathError_EFBIG,
	writeToFilePathError_PRINT_EINTR,
	writeToFilePathError_EIO,
	writeToFilePathError_EPIPE,
	writeToFilePathError_EILSEQ,
	writeToFilePathError_PRINT_EOVERFLOW,
	writeToFilePathError_CLOSE_EAGAIN,
	writeToFilePathError_CLOSE_EFBIG,
	writeToFilePathError_CLOSE_EINTR,
	writeToFilePathError_CLOSE_EIO,
	writeToFilePathError_CLOSE_ENOMEM,
	writeToFilePathError_CLOSE_ENOSPC,
	writeToFilePathError_CLOSE_EPIPE,
	writeToFilePathError_CLOSE_ENXIO,
	writeToFilePathError_EMLINK,
};

enum writeToFilePathError writeToFilePath(const char path[], int pathLength, const char contents[])
{
	enum writeToFilePathError returnValue = SUCCESS;
	int error;

	int parentDirectoryEndIndex;
	int something;
	while (true)
	{
		error = writeToFile(path, pathLength, contents);
		if (error != SUCCESS)
		{
			switch (error)
			{
				case writeToFileError_EACCES:
					returnValue = writeToFilePathError_EACCES;
					break;
				case writeToFileError_OPEN_EINTR:
					returnValue = writeToFilePathError_OPEN_EINTR;
					break;
				case writeToFileError_EISDIR:
					returnValue = writeToFilePathError_EISDIR;
					break;
				case writeToFileError_ELOOP:
					returnValue = writeToFilePathError_ELOOP;
					break;
				case writeToFileError_EMFILE:
					returnValue = writeToFilePathError_EMFILE;
					break;
				case writeToFileError_ENAMETOOLONG:
					returnValue = writeToFilePathError_ENAMETOOLONG;
					break;
				case writeToFileError_ENFILE:
					returnValue = writeToFilePathError_ENFILE;
					break;
				case writeToFileError_ENOENT:
					parentDirectoryEndIndex = getParentDirectory(path, pathLength - 1, "\\", 1);
					error = mkdirectorytraversal(path, parentDirectoryEndIndex);
					if (error != SUCCESS)
					{
						switch (error)
						{
							case mkdirectorytraversalError_EACCES:
								returnValue = writeToFilePathError_EACCES;
								break;
							case mkdirectorytraversalError_ELOOP:
								returnValue = writeToFilePathError_ELOOP;
								break;
							case mkdirectorytraversalError_EMLINK:
								returnValue = writeToFilePathError_EMLINK;
								break;
							case mkdirectorytraversalError_ENAMETOOLONG:
								returnValue = writeToFilePathError_ENAMETOOLONG;
								break;
							case mkdirectorytraversalError_ENOSPC:
								returnValue = writeToFilePathError_ENOSPC;
								break;
							case mkdirectorytraversalError_ENOTDIR:
								returnValue = writeToFilePathError_ENOTDIR;
								break;
							case mkdirectorytraversalError_EROFS:
								returnValue = writeToFilePathError_EROFS;
								break;
							case mkdirectorytraversalError_ENOMEM:
								returnValue = writeToFilePathError_ENOMEM;
								break;
							default:
								returnValue = writeToFilePathError_BUG;
								break;
						}

						break;
					}

					continue;
				case writeToFileError_ENOSPC:
					returnValue = writeToFilePathError_ENOSPC;
					break;
				case writeToFileError_ENOTDIR:
					returnValue = writeToFilePathError_ENOTDIR;
					break;
				case writeToFileError_ENXIO:
					returnValue = writeToFilePathError_ENXIO;
					break;
				case writeToFileError_OPEN_EOVERFLOW:
					returnValue = writeToFilePathError_OPEN_EOVERFLOW;
					break;
				case writeToFileError_EROFS:
					returnValue = writeToFilePathError_EROFS;
					break;
				case writeToFileError_EINVAL:
					returnValue = writeToFilePathError_EINVAL;
					break;
				case writeToFileError_ENOMEM:
					returnValue = writeToFilePathError_ENOMEM;
					break;
				case writeToFileError_ETXTBSY:
					returnValue = writeToFilePathError_ETXTBSY;
					break;
				case writeToFileError_EAGAIN:
					returnValue = writeToFilePathError_EAGAIN;
					break;
				case writeToFileError_EFBIG:
					returnValue = writeToFilePathError_EFBIG;
					break;
				case writeToFileError_PRINT_EINTR:
					returnValue = writeToFilePathError_PRINT_EINTR;
					break;
				case writeToFileError_EIO:
					returnValue = writeToFilePathError_EIO;
					break;
				case writeToFileError_EPIPE:
					returnValue = writeToFilePathError_EPIPE;
					break;
				case writeToFileError_EILSEQ:
					returnValue = writeToFilePathError_EILSEQ;
					break;
				case writeToFileError_PRINT_EOVERFLOW:
					returnValue = writeToFilePathError_PRINT_EOVERFLOW;
					break;
				case writeToFileError_CLOSE_EAGAIN:
					returnValue = writeToFilePathError_CLOSE_EAGAIN;
					break;
				case writeToFileError_CLOSE_EFBIG:
					returnValue = writeToFilePathError_CLOSE_EFBIG;
					break;
				case writeToFileError_CLOSE_EINTR:
					returnValue = writeToFilePathError_CLOSE_EINTR;
					break;
				case writeToFileError_CLOSE_EIO:
					returnValue = writeToFilePathError_CLOSE_EIO;
					break;
				case writeToFileError_CLOSE_ENOMEM:
					returnValue = writeToFilePathError_CLOSE_ENOMEM;
					break;
				case writeToFileError_CLOSE_ENOSPC:
					returnValue = writeToFilePathError_CLOSE_ENOSPC;
					break;
				case writeToFileError_CLOSE_EPIPE:
					returnValue = writeToFilePathError_CLOSE_EPIPE;
					break;
				case writeToFileError_CLOSE_ENXIO:
					returnValue = writeToFilePathError_CLOSE_ENXIO;
					break;
				default:
					returnValue = writeToFileError_BUG;
					break;
			}

			goto finally;
		}
	}

finally:
	return returnValue;
}

int main()
{
	//// TODO make is so that you can use a path that doesn't exist
	//// TODO separate into a few files
	//// TODO some of your error codes aren't actually possible (for example, EINVAL in the `writeToFile` can't come from `fopen`)
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