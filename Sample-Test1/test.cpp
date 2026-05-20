#include "pch.h"

#include <std.io>
#include <time.h>

#include "..\Project3\arraylength.h"
#include "..\Project3\errors.h"
#include "..\Project3\directories.h"






TEST(WriteToFile, WriteToFile)
{
	int error;

	char* workingDirectory;
	error = generatecwd(&workingDirectory);
	EXPECT_EQ(SUCCESS, error);

	char timestampFormat[] = "%Y-%m-%d %H:%M:%S"; //// TODO do milliseconds
	char timestamp[ARRAY_LENGTH(timestampFormat)]; //// TODO this length computation doesn't actaully work
	time_t now = time(NULL);
	struct tm* localTime = localtime(&now);

	strftime(timestamp, ARRAY_LENGTH(timestamp), timestampFormat, localTime);




	EXPECT_TRUE(false) << workingDirectory << "qwer";
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