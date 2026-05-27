#include "pch.h"

//#include <std.io>
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
	char* combinePath(
		const char* separator, 
		const int separatorLength, 
		const char* path1,
		const int path1Length, 
		const char* path2,
		const int path2Length)
	{
		return 0;
	}
}

TEST(WriteToFile, WriteToFile)
{
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