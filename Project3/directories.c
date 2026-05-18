#include "directories_private.h"

int getParentDirectory(const char path[], const int endIndex, const char directoryDelimiter[], const int delimiterLength)
{
	int parentIndex = endIndex;
	if (substrcmp(path, parentIndex - delimiterLength, directoryDelimiter, 0, delimiterLength))
	{
		parentIndex = parentIndex - delimiterLength;
	}

	while (parentIndex >= 0 && !substrcmp(path, parentIndex - delimiterLength, directoryDelimiter, 0, delimiterLength))
	{
		--parentIndex;
	}

	return parentIndex;
}

enum ravudetmkdirError ravudetmkdir(const char path[])
{
	enum ravudetmkdirError returnValue = SUCCESS;

	if (path == NULL)
	{
		returnValue = ravudetmkdirError_NULLPOINTER;
		goto finally;
	}

	int mkdirError = mkdir(path);
	if (mkdirError == -1)
	{
		int error = errno;
		switch (error)
		{
			case EACCES:
				returnValue = ravudetmkdirError_EACCES;
				break;
			case EEXIST:
				returnValue = ravudetmkdirError_EEXIST;
				break;
			case ELOOP:
				returnValue = ravudetmkdirError_ELOOP;
				break;
			case EMLINK:
				returnValue = ravudetmkdirError_EMLINK;
				break;
			case ENAMETOOLONG:
				returnValue = ravudetmkdirError_ENAMETOOLONG;
				break;
			case ENOENT:
				returnValue = ravudetmkdirError_ENOENT;
				break;
			case ENOSPC:
				returnValue = ravudetmkdirError_ENOSPC;
				break;
			case ENOTDIR:
				returnValue = ravudetmkdirError_ENOTDIR;
				break;
			case EROFS:
				returnValue = ravudetmkdirError_EROFS;
				break;
			default:
				returnValue = ravudetmkdirError_BUG;
				break;
		}

		goto finally;
	}

	finally:
	return returnValue;
}

enum mksubdirError mksubdir(const char path[], const int endIndex)
{
	enum mksubdirError returnValue = SUCCESS;
	int error;

	char* subPath;
	error = substring(path, endIndex, &subPath);
	if (error != SUCCESS)
	{
		switch (error)
		{
			case substringError_ENOMEM:
				returnValue = mksubdirError_ENOMEM;
				break;
			default:
				returnValue = mksubdirError_BUG;
				break;
		}

		goto finally;
	}

	error = ravudetmkdir(subPath);
	if (error != SUCCESS)
	{
		switch (error)
		{
			case ravudetmkdirError_EACCES:
				returnValue = mksubdirError_EACCES;
				break;
			case ravudetmkdirError_EEXIST:
				returnValue = mksubdirError_EEXIST;
				break;
			case ravudetmkdirError_ELOOP:
				returnValue = mksubdirError_ELOOP;
				break;
			case ravudetmkdirError_EMLINK:
				returnValue = mksubdirError_EMLINK;
				break;
			case ravudetmkdirError_ENAMETOOLONG:
				returnValue = mksubdirError_ENAMETOOLONG;
				break;
			case ravudetmkdirError_ENOENT:
				returnValue = mksubdirError_ENOENT;
				break;
			case ravudetmkdirError_ENOSPC:
				returnValue = mksubdirError_ENOSPC;
				break;
			case ravudetmkdirError_ENOTDIR:
				returnValue = mksubdirError_ENOTDIR;
				break;
			case ravudetmkdirError_EROFS:
				returnValue = mksubdirError_EROFS;
				break;
			default:
				returnValue = mksubdirError_BUG;
				break;
		}

		goto finally;
	}

	finally:
	free(subPath);
	return returnValue;
}

enum mkdirectorytraversalError mkdirectorytraversal(const char directoryPath[], int pathLength)
{
	const char delimiter[] = "\\";

	enum mkdirectorytraversalError returnValue = SUCCESS;
	int error;

	int parentDirectoryEndIndex;
	error = mksubdirError_ENOENT;
	while (error == mksubdirError_ENOENT)
	{
		error = mksubdir(directoryPath, pathLength - 1);
		if (error != SUCCESS)
		{
			switch (error)
			{
			case mksubdirError_EACCES:
				returnValue = mkdirectorytraversalError_EACCES;
				break;
			case mksubdirError_EEXIST:
				break;
			case mksubdirError_ELOOP:
				returnValue = mkdirectorytraversalError_ELOOP;
				break;
			case mksubdirError_EMLINK:
				returnValue = mkdirectorytraversalError_EMLINK;
				break;
			case mksubdirError_ENAMETOOLONG:
				returnValue = mkdirectorytraversalError_ENAMETOOLONG;
				break;
			case mksubdirError_ENOENT:
				parentDirectoryEndIndex = getParentDirectory(directoryPath, pathLength - 1, delimiter, (sizeof(delimiter) / sizeof(delimiter[0])) - 1);
				returnValue = mkdirectorytraversal(directoryPath, parentDirectoryEndIndex);
				if (returnValue == SUCCESS)
				{
					continue;
				}
				else
				{
					break;
				}
			case mksubdirError_ENOSPC:
				returnValue = mkdirectorytraversalError_ENOSPC;
				break;
			case mksubdirError_ENOTDIR:
				returnValue = mkdirectorytraversalError_ENOTDIR;
				break;
			case mksubdirError_EROFS:
				returnValue = mkdirectorytraversalError_EROFS;
				break;
			case mksubdirError_ENOMEM:
				returnValue = mkdirectorytraversalError_ENOMEM;
				break;
			default:
				returnValue = mkdirectorytraversalError_BUG;
				break;
			}

			goto finally;
		}
	}

	finally:
	return returnValue;
}

enum ravudetgetcwdError ravudetgetcwd(char buf[], size_t size, char** cwd)
{
	enum ravudetgetcwdError returnValue = SUCCESS;

	cwd = _getcwd(NULL, 0);

	if (*cwd == NULL)
	{
		int error = errno;
		switch (error)
		{
		case EACCES:
			returnValue = ravudetgetcwdError_EACCES;
			break;
		case EFAULT:
			returnValue = ravudetgetcwdError_EFAULT;
			break;
		case EINVAL:
			returnValue = ravudetgetcwdError_EINVAL;
			break;
		case ENAMETOOLONG:
			returnValue = ravudetgetcwdError_ENAMETOOLONG;
			break;
		case ENOENT:
			returnValue = ravudetgetcwdError_ENOENT;
			break;
		case ENOMEM:
			returnValue = ravudetgetcwdError_ENOMEM;
			break;
		case ERANGE:
			returnValue = ravudetgetcwdError_ERANGE;
			break;
		default:
			returnValue = ravudetgetcwdError_BUG;
			break;
		}

		goto finally;
	}

	finally:
	return returnValue;
}

enum generatecwdError generatecwd(char** cwd)
{
	enum generatecwdError returnValue = SUCCESS;
	int error;

	error = ravudetgetcwd(NULL, 0, cwd);
	if (error != SUCCESS)
	{
		switch (error)
		{
		case ravudetgetcwdError_EACCES:
			returnValue = generatecwdError_EACCES;
			break;
		case ravudetgetcwdError_ENAMETOOLONG:
			returnValue = generatecwdError_ENAMETOOLONG;
			break;
		case ravudetgetcwdError_ENOENT:
			returnValue = generatecwdError_ENOENT;
			break;
		case ravudetgetcwdError_ENOMEM:
			returnValue = generatecwdError_ENOMEM;
			break;
		default:
			returnValue = generatecwdError_BUG;
			break;
		}

		goto catch;
	}

	finally:
	return returnValue;

	catch:
	free(cwd);
	goto finally;
}