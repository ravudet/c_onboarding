#include "pch.h"

#if defined _WIN32
#include <direct.h>
#define getcwd _getcwd
#elif defined __linux__
#include <unistd.h>
#endif


#include "..\Project3\directories.h"






TEST(WriteToFile, WriteToFile)
{
	int error;

	char* workingDirectory;
	error = generatecwd(&workingDirectory);
	if (error != 0)
	{
		//// TODO
	}



	////char* workingDirectory = getcwd(NULL, 0);
	EXPECT_TRUE(false) << workingDirectory << "workingDirectory";
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