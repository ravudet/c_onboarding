#include "main_private.h"

// https://pubs.opengroup.org/onlinepubs/9699919799/functions/fclose.html

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

enum mainError
{
	mainError_BUG = 1,
	mainError_EACCES,
	mainError_OPEN_EINTR,
	mainError_EISDIR,
	mainError_ELOOP,
	mainError_EMFILE,
	mainError_ENAMETOOLONG,
	mainError_ENFILE,
	mainError_ENOSPC,
	mainError_ENOTDIR,
	mainError_ENXIO,
	mainError_OPEN_EOVERFLOW,
	mainError_EROFS,
	mainError_EINVAL,
	mainError_ENOMEM,
	mainError_ETXTBSY,
	mainError_EAGAIN,
	mainError_EFBIG,
	mainError_PRINT_EINTR,
	mainError_EIO,
	mainError_EPIPE,
	mainError_EILSEQ,
	mainError_PRINT_EOVERFLOW,
	mainError_CLOSE_EAGAIN,
	mainError_CLOSE_EFBIG,
	mainError_CLOSE_EINTR,
	mainError_CLOSE_EIO,
	mainError_CLOSE_ENOMEM,
	mainError_CLOSE_ENOSPC,
	mainError_CLOSE_EPIPE,
	mainError_CLOSE_ENXIO,
};

enum mainError main()
{
	
	//// TODO put array length macro in its own file (a private include header)
	//// TODO make sure you still have the spacing correct in this file (compare it to your other files)
	//// TODO some of your error codes aren't actually possible (for example, EINVAL in the `writeToFile` can't come from `fopen`)
	//// TODO write a unit test to confirm that the file was written
	//// TODO go through TODOs

	enum mainError returnValue = SUCCESS;
	int error;

	char path[] = "c:\\users\\ravud\\test\\test2\\test.txt";
	error = writeToFilePath(path, LENGTH(path), "contents");
	if (error != SUCCESS)
	{
		switch (error)
		{
		case writeToFilePathError_EACCES:
			returnValue = mainError_EACCES;
			break;
		case writeToFilePathError_OPEN_EINTR:
			returnValue = mainError_OPEN_EINTR;
			break;
		case writeToFilePathError_EISDIR:
			returnValue = mainError_EISDIR;
			break;
		case writeToFilePathError_ELOOP:
			returnValue = mainError_ELOOP;
			break;
		case writeToFilePathError_EMFILE:
			returnValue = mainError_EMFILE;
			break;
		case writeToFilePathError_ENAMETOOLONG:
			returnValue = mainError_ENAMETOOLONG;
			break;
		case writeToFilePathError_ENOSPC:
			returnValue = mainError_ENOSPC;
			break;
		case writeToFilePathError_ENOTDIR:
			returnValue = mainError_ENOTDIR;
			break;
		case writeToFilePathError_ENXIO:
			returnValue = mainError_ENXIO;
			break;
		case writeToFilePathError_OPEN_EOVERFLOW:
			returnValue = mainError_OPEN_EOVERFLOW;
			break;
		case writeToFilePathError_EROFS:
			returnValue = mainError_EROFS;
			break;
		case writeToFilePathError_EINVAL:
			returnValue = mainError_EINVAL;
			break;
		case writeToFilePathError_ENOMEM:
			returnValue = mainError_ENOMEM;
			break;
		case writeToFilePathError_ETXTBSY:
			returnValue = mainError_ETXTBSY;
			break;
		case writeToFilePathError_EAGAIN:
			returnValue = mainError_EAGAIN;
			break;
		case writeToFilePathError_EFBIG:
			returnValue = mainError_EFBIG;
			break;
		case writeToFilePathError_PRINT_EINTR:
			returnValue = mainError_PRINT_EINTR;
			break;
		case writeToFilePathError_EIO:
			returnValue = mainError_EIO;
			break;
		case writeToFilePathError_EPIPE:
			returnValue = mainError_EPIPE;
			break;
		case writeToFilePathError_EILSEQ:
			returnValue = mainError_EILSEQ;
			break;
		case writeToFilePathError_PRINT_EOVERFLOW:
			returnValue = mainError_PRINT_EOVERFLOW;
			break;
		case writeToFilePathError_CLOSE_EAGAIN:
			returnValue = mainError_CLOSE_EAGAIN;
			break;
		case writeToFilePathError_CLOSE_EFBIG:
			returnValue = mainError_CLOSE_EFBIG;
			break;
		case writeToFilePathError_CLOSE_EINTR:
			returnValue = mainError_CLOSE_EINTR;
			break;
		case writeToFilePathError_CLOSE_EIO:
			returnValue = mainError_CLOSE_EIO;
			break;
		case writeToFilePathError_CLOSE_ENOMEM:
			returnValue = mainError_CLOSE_ENOMEM;
			break;
		case writeToFilePathError_CLOSE_ENOSPC:
			returnValue = mainError_CLOSE_ENOSPC;
			break;
		case writeToFilePathError_CLOSE_EPIPE:
			returnValue = mainError_CLOSE_EPIPE;
			break;
		case writeToFilePathError_CLOSE_ENXIO:
			returnValue = mainError_CLOSE_ENXIO;
			break;
		default:
			returnValue = mainError_BUG;
			break;
		}

		goto catch;
	}

	finally:
	printf("press any key to continue");
	int c = fgetc(stdin);
	return returnValue;

	catch:
	printf("ERROR! %d", returnValue);
	goto finally;
}