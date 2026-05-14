#include "pch.h"

#if defined _WIN32
#include <direct.h>
#define getcwd _getcwd
#elif defined __linux__
#include <unistd.h>
#endif

#define MAX_BUF 1024

TEST(WriteToFile, WriteToFile)
{
	char path[MAX_BUF];
	if (getcwd(path, MAX_BUF) != NULL) {
		printf("Current working directory: %s\n", path);
	}
	else {
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}



	char* path2;
	path2 = (char*)malloc(MAX_BUF);
	getcwd(path2, MAX_BUF);
	free(path2);



	char* path3 = NULL;
	path3 = getcwd(path3, MAX_BUF);
	free(path3);


	char* path4 = NULL;
	path4 = getcwd(path4, 0);
	//EXPECT_TRUE(false) << path4 << "!234a";
	free(path4);




	char* path5 = getcwd(NULL, 0);
	EXPECT_TRUE(false) << path5 << "zxcv";
	free(path5);





	char* workingDirectory = getcwd(NULL, 0);

	::testing::ScopedTrace trace(__FILE__, __LINE__, "test");

	SCOPED_TRACE("qwer");

	std::cout << workingDirectory;
	////throw "sadf";
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