#include "pch.h"

#if defined _WIN32
#include <direct.h>
#define getcwd _getcwd
#elif defined __linux__
#include <unistd.h>
#endif

#define EXPECT_NONFATAL_FAILURE 

TEST(WriteToFile, WriteToFile)
{
	char* workingDirectory = getcwd(NULL, 0);

	::testing::ScopedTrace trace(__FILE__, __LINE__, "test");

	SCOPED_TRACE("qwer");

	std::cout << workingDirectory;
	////throw "sadf";
	free(workingDirectory);

	EXPECT_TRUE(false) << workingDirectory;
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