#include "main_private.h"

//// TODO write a unit test to confirm that the file was written
//// TODO did you put `const` everywhere it's applicable?
//// TODO do you have binary and build files in the repo?
//// TODO go through TODOs
//// TODO you are done with your onboarding; now you can play around with the string stuff in `strs.c`

enum mainError main()
{
	enum mainError returnValue = SUCCESS;
	int error;

	char path[] = "c:\\users\\ravud\\test\\test2\\test.txt";
	error = writeToFilePath(path, ARRAY_LENGTH(path), "contents"); //// TODO this is currently appending, is that the desired behavior?
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
		case writeToFilePathError_ENOMEM:
			returnValue = mainError_ENOMEM;
			break;
		case writeToFilePathError_ETXTBSY:
			returnValue = mainError_ETXTBSY;
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
		case writeToFilePathError_EILSEQ:
			returnValue = mainError_EILSEQ;
			break;
		case writeToFilePathError_PRINT_EOVERFLOW:
			returnValue = mainError_PRINT_EOVERFLOW;
			break;
		case writeToFilePathError_CLOSE_EFBIG:
			returnValue = mainError_CLOSE_EFBIG;
			break;
		case writeToFilePathError_CLOSE_EINTR:
			returnValue = mainError_CLOSE_EINTR;
			break;
		case writeToFilePathError_CLOSE_ENOSPC:
			returnValue = mainError_CLOSE_ENOSPC;
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