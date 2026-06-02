#include "pch.h"

//#include <std.io>
#include <string.h>
#include <time.h>

#include "..\Project3\arraylength.h"
#include "..\Project3\errors.h"
#include "..\Project3\directories.h"




extern "C" {
	int timestampFormatLength(const char* format)
	{
		//// TODO null check
		//// TODO assumes whatever it is that my locale is

		int length = 0;
		for (int i = 0; i < format[i] != '\0'; ++i)
		{
			if (format[i] == '%')
			{
				++i;
				switch (format[i])
				{
				case 'Y':
					length += 4;
					break;
				case 'm':
					length += 2;
					break;
				case 'd':
					length += 2;
					break;
				case 'H':
					length += 2;
					break;
				case 'M':
					length += 2;
					break;
				case 'S':
					length += 2;
					break;
				////default:
					//// TODO unknown/not supported (these are actually different, you should go through all of the values [here](https://pubs.opengroup.org/onlinepubs/9699919799/functions/strftime.html) and figure out which ones you can't use because of locale; those should be "unsupported"; everything else is "feature gap" or "supported" or "unknown"
				}

				continue;
			}
			else
			{
				++length;
			}
		}

		return length + 1; // null terminator
	}

	//// TODO https://pubs.opengroup.org/onlinepubs/9699919799/functions/strcat.html
	enum combinePathError
	{
		combinePathError_BUG = 1,
		combinePathError_ENOMEM,
	};
	enum combinePathError combinePath(
		const char* separator, 
		const int separatorLength, 
		const char* path1,
		const int path1Length, 
		const char* path2,
		const int path2Length,
		char** combinedPath) //// TODO `const`?
	{
		//// TODO what about leading or trailing separators?
		//// TODO you should have a string combining method, and then `combinePath` should leverage that

		enum combinePathError returnValue = (combinePathError)SUCCESS; //// TODO why do you have to cast here, but not in other files?

		*combinedPath = (char*)malloc(path1Length + separatorLength + path2Length - 1); // -2 because of 3 null terminators
		if (*combinedPath == NULL)
		{
			//// TODO check `errno` actually
			returnValue = combinePathError_ENOMEM;
			goto catch2;
		}

		memcpy((void*)*combinedPath, path1, path1Length);
		void* endOfFirst = ((char*)*combinedPath) + path1Length - 1;
		memcpy(endOfFirst, separator, separatorLength);
		void* endOfSeparator = (char*)endOfFirst + separatorLength - 1;
		memcpy(endOfSeparator, path2, path2Length);

		finally:
		return returnValue;

		catch2: //// TODO "catch"
		free(*combinedPath);
		goto finally;
	}

	struct string
	{
		const char* value;
		const int length; // this *does not* include the null terminator
	};

	static inline string createString(const char string[], const int length)
	{
		return { string, length };
	}

	enum concatStringError
	{
		concatStringError_BUG = 1,
		concatStringError_ENOMEM,
	};
	concatStringError concatString(const string first, const string second, string* concated) //// TODO variable parameter list
	{
		enum concatStringError returnValue = (concatStringError)SUCCESS; //// TODO shouldn't have to cast

		int arrayLength = first.length + second.length + 1; // +1 because we need a null terminator
		char* array = (char*)malloc(arrayLength);
		if (array == NULL)
		{
			//// TODO check `errno` actually
			returnValue = concatStringError_ENOMEM;
			goto catch2;
		}

		memcpy(array, first.value, first.length);
		memcpy(array, second.value, second.length);
		array[arrayLength - 1] = '\0';

		finally:
		return returnValue;

		catch2: //// TODO catch
		free(array);
		goto finally;
	}

#define CREATE_STRING(x) (createString(x, ARRAY_LENGTH(x) - 1))
#define CREATE_STRING_SLOW(x) (createString(x, strlen(x) - 1))
}

TEST(WriteToFile, WriteToFile)
{
	char something[] = "asdfas";
	//string str = createString(something);

	string str = CREATE_STRING(something);

	/*int somethingelse[] = {1, 2, 3};
	string str2 = CREATE_STRING(somethingelse);*/

	//// TODO use `ASSERT_*` instead of `EXPECT_*`
	int error;

	char* workingDirectory;
	error = generatecwd(&workingDirectory);
	EXPECT_EQ(SUCCESS, error);

	char timestampFormat[] = "%Y-%m-%d %H:%M:%S";
	int timestampLength = timestampFormatLength(timestampFormat);
	char* timestamp = (char*)malloc(timestampLength);
	if (timestamp == NULL)
	{
		//// TODO
		return;
	}

	time_t now = time(NULL);
	struct tm* localTime = localtime(&now);

	strftime(timestamp, timestampLength, timestampFormat, localTime);



	char separator[] = "\\";
	char* combinedPath;
	//// TODO do better then `strlen`
	combinePath(separator, ARRAY_LENGTH(separator), workingDirectory, strlen(workingDirectory) + 1, timestamp, timestampLength, &combinedPath);



	ASSERT_TRUE(false) << combinedPath;
	ASSERT_TRUE(false) << workingDirectory << "qwer" << timestampLength << timestamp;



	free(timestamp);
	free(workingDirectory);

}





// TODO Tools > Options > Test Adapter for Google Test -> print test output










TEST(TestCaseName1, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(another, again)
{
	EXPECT_TRUE(false);
}


TEST(third, more)
{
	////std::cout << "error: Value of: false\r\n  Actual : false\r\nExpected : true";
	EXPECT_TRUE(true);
}