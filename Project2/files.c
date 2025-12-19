#include "files.h"

enum ravudetfopenError ravudetfopen(const char filePath[], const char* mode, const FILE** fileHandle)
{
	enum ravudetfopenError returnValue = SUCCESS;

#pragma warning(suppress : 4996) // we are preferring portability over supposed "security"
	* fileHandle = fopen(filePath, mode);

	if (*fileHandle == NULL)
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

enum writeToFilePathError writeToFilePath(const char path[], int pathLength, const char contents[])
{
	enum writeToFilePathError returnValue = SUCCESS;
	int error;

	int parentDirectoryEndIndex;
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
				returnValue = writeToFilePathError_BUG;
				break;
			}

			goto finally;
		}

		break;
	}

	finally:
	return returnValue;
}