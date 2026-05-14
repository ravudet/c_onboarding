#include "pch.h"

#if defined _WIN32
#include <direct.h>
#define getcwd _getcwd
#elif defined __linux__
#include <unistd.h>
#endif






enum ravudetgetcwdError
{
	ravudetfopenError_BUG = 1,
	ravudetfopenError_EACCES,
	ravudetfopenError_EINTR,
	ravudetfopenError_EISDIR,
	ravudetfopenError_ELOOP,
	ravudetfopenError_EMFILE,
	ravudetfopenError_ENAMETOOLONG,
	ravudetfopenError_ENFILE,
	ravudetfopenError_ENOENT,
	ravudetfopenError_ENOSPC,
	ravudetfopenError_ENOTDIR,
	ravudetfopenError_ENXIO,
	ravudetfopenError_EOVERFLOW,
	ravudetfopenError_EROFS,
	ravudetfopenError_EINVAL,
	ravudetfopenError_ENOMEM,
	ravudetfopenError_ETXTBSY,
};
enum ravudetgetcwdError ravudetgetcwd(char buf[], size_t size, char** cwd)
{
	//// https://www.man7.org/linux/man-pages/man3/getcwd.3.html
	//// TODO you are here, mimicing `ravudetfopen`
}







TEST(WriteToFile, WriteToFile)
{
	char* workingDirectory = getcwd(NULL, 0);
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