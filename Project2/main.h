#pragma once

enum mainError
{
	mainError_BUG = 1,
	mainError_EACCES,
	mainError_OPEN_EINTR,
	mainError_EISDIR,
	mainError_ELOOP,
	mainError_EMFILE,
	mainError_ENAMETOOLONG,
	mainError_ENFILE,
	mainError_ENOSPC,
	mainError_ENOTDIR,
	mainError_ENXIO,
	mainError_OPEN_EOVERFLOW,
	mainError_EROFS,
	mainError_EINVAL,
	mainError_ENOMEM,
	mainError_ETXTBSY,
	mainError_EAGAIN,
	mainError_EFBIG,
	mainError_PRINT_EINTR,
	mainError_EIO,
	mainError_EPIPE,
	mainError_EILSEQ,
	mainError_PRINT_EOVERFLOW,
	mainError_CLOSE_EAGAIN,
	mainError_CLOSE_EFBIG,
	mainError_CLOSE_EINTR,
	mainError_CLOSE_EIO,
	mainError_CLOSE_ENOMEM,
	mainError_CLOSE_ENOSPC,
	mainError_CLOSE_EPIPE,
	mainError_CLOSE_ENXIO,
};

enum mainError main();