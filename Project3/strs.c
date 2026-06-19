#include "strs_private.h"

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

	finally:
	return returnValue;

	catch:
	free(substring);
	goto finally;
}

bool substrcmp(const char x[], const int xStart, const char y[], const int yStart, const int length)
{
	return memcmp(x + xStart, y + yStart, length) == 0;
}







typedef const struct string
{
	const char* value;
	const int length; // this *does not* include the null terminator
} string;

const typedef struct concatedString
{
	const char* value;
	const int totalLength;
	const concatedString* antecedent;
} concatedString;

concatedString concatString2(const string first)
{
	//// TODO you are here
	//// TODO you've lost the plot a bit, you're trying to combine paths; maybe get the scaffolding of that working so that you can actually write your test, and *then* proceed to optimizing stuff around string allocations

	struct concatedString foo = { first.value, first.length, NULL };
	return foo;
}

concatedString concatString3(const concatedString* first, const string second)
{
	struct concatedString foo = { second.value, second.length + (*first).totalLength, first };
	return foo;
}




const typedef struct concatedString2
{
	const concatedString* first;
	const concatedString* second;
} concatedString2;

concatedString concatString4(const concatedString* first, const concatedString* second)
{
}




const typedef union concatedStringUnion
{
	concatedString concatedString;
	concatedString2 concatedString2;
} concatedStringUnion;
const typedef struct concatedStringCombined
{
	int type;
	concatedStringUnion string;
} concatedStringCombined;


string concatedStringToString(const concatedString string)
{
	int arrayLength = string.totalLength + 1;
	char* array = (char*)malloc(arrayLength);
	if (array == NULL)
	{
		//// TODO
	}

	array[arrayLength - 1] = '\0';

	concatedString* current = &string;
	for (current = &string; current->antecedent != NULL; current = current->antecedent)
	{
		int stringLength = current->totalLength - current->antecedent->totalLength;
		memcpy(array, current->value, stringLength); //// TODO `memcpy` always write at the beginning of the destination
	}

	memcpy(array, current->value, current->totalLength);

	struct string foo = { array, arrayLength - 1 };
	return foo; //// TODO i think you're proving that you're pointer "out" parameter pattern doesn't actually work because you will need to malloc, or they will need to initialize
}





string concatedStringUnionToString(const concatedStringCombined string)
{
	switch (string.type)
	{
	case 0:
		return concatedStringToString(string.string.concatedString);
	}
}