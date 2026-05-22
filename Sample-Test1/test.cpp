#include "pch.h"

//#include <std.io>
#include <time.h>

#include "..\Project3\arraylength.h"
#include "..\Project3\errors.h"
#include "..\Project3\directories.h"




extern "C" {
	int TimestampFormatLength(const char* format)
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
				case 'm':
					length += 2;
				case 'd':
					length += 2;
				case 'H':
					length += 2;
				case 'M':
					length += 2;
				case 'S':
					length += 2;
				default:
					//// TODO unknown/not supported (these are actually different, you should go through all of the values [here](https://pubs.opengroup.org/onlinepubs/9699919799/functions/strftime.html) and figure out which ones you can't use because of locale; those should be "unsupported"; everything else is "feature gap" or "supported" or "unknown"
				}

				continue;
			}
			else
			{
				++length;
			}
		}

		return length;
	}
}

TEST(WriteToFile, WriteToFile)
{
	int error;

	char* workingDirectory;
	error = generatecwd(&workingDirectory);
	EXPECT_EQ(SUCCESS, error);

	char timestampFormat[] = "%Y-%m-%d %H:%M:%S"; //// TODO do milliseconds
	//char timestamp[ARRAY_LENGTH(timestampFormat)]; //// TODO this length computation doesn't actaully work
	char timestamp[50];
	time_t now = time(NULL);
	struct tm* localTime = localtime(&now);

	strftime(timestamp, ARRAY_LENGTH(timestamp), timestampFormat, localTime);




	EXPECT_TRUE(false) << workingDirectory << "qwer" << timestamp;
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