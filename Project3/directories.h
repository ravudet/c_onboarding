#pragma once

int getParentDirectory(const char path[], const int endIndex, const char directoryDelimiter[], const int delimiterLength);

enum ravudetmkdirError
{
	ravudetmkdirError_BUG = 1,
	ravudetmkdirError_NULLPOINTER,
	ravudetmkdirError_EACCES,
	ravudetmkdirError_EEXIST,
	ravudetmkdirError_ELOOP,
	ravudetmkdirError_EMLINK,
	ravudetmkdirError_ENAMETOOLONG,
	ravudetmkdirError_ENOENT,
	ravudetmkdirError_ENOSPC,
	ravudetmkdirError_ENOTDIR,
	ravudetmkdirError_EROFS,
};
enum ravudetmkdirError ravudetmkdir(const char path[]);

enum mksubdirError
{
	mksubdirError_BUG = 1,
	mksubdirError_EACCES,
	mksubdirError_EEXIST,
	mksubdirError_ELOOP,
	mksubdirError_EMLINK,
	mksubdirError_ENAMETOOLONG,
	mksubdirError_ENOENT,
	mksubdirError_ENOSPC,
	mksubdirError_ENOTDIR,
	mksubdirError_EROFS,
	mksubdirError_ENOMEM,
};
enum mksubdirError mksubdir(const char path[], const int endIndex);

enum mkdirectorytraversalError
{
	mkdirectorytraversalError_BUG = 1,
	mkdirectorytraversalError_EACCES,
	mkdirectorytraversalError_ELOOP,
	mkdirectorytraversalError_EMLINK,
	mkdirectorytraversalError_ENAMETOOLONG,
	mkdirectorytraversalError_ENOSPC,
	mkdirectorytraversalError_ENOTDIR,
	mkdirectorytraversalError_EROFS,
	mkdirectorytraversalError_ENOMEM,
};
enum mkdirectorytraversalError mkdirectorytraversal(const char directoryPath[], int pathLength);

enum ravudetgetcwdError
{
	ravudetgetcwdError_BUG = 1,
	ravudetgetcwdError_EACCES,
	ravudetgetcwdError_EFAULT,
	ravudetgetcwdError_EINVAL,
	ravudetgetcwdError_ENAMETOOLONG,
	ravudetgetcwdError_ENOENT,
	ravudetgetcwdError_ENOMEM,
	ravudetgetcwdError_ERANGE,
};
enum ravudetgetcwdError ravudetgetcwd(char buf[], size_t size, char** cwd);

enum generatecwdError
{
	generatecwdError_BUG = 1,
	generatecwdError_EACCES,
	generatecwdError_ENAMETOOLONG,
	generatecwdError_ENOENT,
	generatecwdError_ENOMEM,
};
enum generatecwdError generatecwd(char** cwd);