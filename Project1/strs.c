#include "strs.h"

/*enum substringError substring(const char string[], const int endIndex, char* substringPointer[])
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

	finally:
	return returnValue;

	catch:
	free(substring);
	goto finally;
}*/