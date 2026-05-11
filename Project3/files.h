#pragma once

#include <stdio.h>

enum ravudetfopenError
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
enum ravudetfopenError ravudetfopen(const char filePath[], const char* mode, const FILE** fileHandle);

enum ravudetfprintfError
{
	ravudetfprintfError_BUG = 1,
	ravudetfprintfError_EAGAIN,
	ravudetfprintfError_EBADF,
	ravudetfprintfError_EFBIG,
	ravudetfprintfError_EINTR,
	ravudetfprintfError_EIO,
	ravudetfprintfError_ENOSPC,
	ravudetfprintfError_EPIPE,
	ravudetfprintfError_ENOMEM,
	ravudetfprintfError_ENXIO,
	ravudetfprintfError_EILSEQ,
	ravudetfprintfError_EOVERFLOW,
};
enum ravudetfprintfError ravudetfprintf(FILE* stream, int* bytesWritten, const char* format, ...);

enum ravudetfcloseError
{
	ravudetfcloseError_BUG = 1,
	ravudetfcloseError_EAGAIN,
	ravudetfcloseError_EBADF,
	ravudetfcloseError_EFBIG,
	ravudetfcloseError_EINTR,
	ravudetfcloseError_EIO,
	ravudetfcloseError_ENOMEM,
	ravudetfcloseError_ENOSPC,
	ravudetfcloseError_EPIPE,
	ravudetfcloseError_ENXIO,
};
enum ravudetfcloseError ravudetfclose(FILE* stream);

enum writeToFileError
{
	writeToFileError_BUG = 1,
	writeToFileError_EACCES,
	writeToFileError_OPEN_EINTR,
	writeToFileError_EISDIR,
	writeToFileError_ELOOP,
	writeToFileError_EMFILE,
	writeToFileError_ENAMETOOLONG,
	writeToFileError_ENFILE,
	writeToFileError_ENOENT,
	writeToFileError_ENOSPC,
	writeToFileError_ENOTDIR,
	writeToFileError_ENXIO,
	writeToFileError_OPEN_EOVERFLOW,
	writeToFileError_EROFS,
	writeToFileError_ENOMEM,
	writeToFileError_ETXTBSY,
	writeToFileError_EFBIG,
	writeToFileError_PRINT_EINTR,
	writeToFileError_EIO,
	writeToFileError_EPIPE,
	writeToFileError_EILSEQ,
	writeToFileError_PRINT_EOVERFLOW,
	writeToFileError_CLOSE_EFBIG,
	writeToFileError_CLOSE_EINTR,
	writeToFileError_CLOSE_ENOSPC,
	writeToFileError_CLOSE_EPIPE,
	writeToFileError_CLOSE_ENXIO,
};
enum writeToFileError writeToFile(const char filePath[], int pathLength, const char contents[]);

enum writeToFilePathError
{
	writeToFilePathError_BUG = 1,
	writeToFilePathError_EACCES,
	writeToFilePathError_OPEN_EINTR,
	writeToFilePathError_EISDIR,
	writeToFilePathError_ELOOP,
	writeToFilePathError_EMFILE,
	writeToFilePathError_ENAMETOOLONG,
	writeToFilePathError_ENFILE,
	writeToFilePathError_ENOSPC,
	writeToFilePathError_ENOTDIR,
	writeToFilePathError_ENXIO,
	writeToFilePathError_OPEN_EOVERFLOW,
	writeToFilePathError_EROFS,
	writeToFilePathError_ENOMEM,
	writeToFilePathError_ETXTBSY,
	writeToFilePathError_EFBIG,
	writeToFilePathError_PRINT_EINTR,
	writeToFilePathError_EIO,
	writeToFilePathError_EPIPE,
	writeToFilePathError_EILSEQ,
	writeToFilePathError_PRINT_EOVERFLOW,
	writeToFilePathError_CLOSE_EFBIG,
	writeToFilePathError_CLOSE_EINTR,
	writeToFilePathError_CLOSE_ENOSPC,
	writeToFilePathError_CLOSE_EPIPE,
	writeToFilePathError_CLOSE_ENXIO,
	writeToFilePathError_EMLINK,
};
enum writeToFilePathError writeToFilePath(const char path[], int pathLength, const char contents[]);