#include "main_private.h"

// https://pubs.opengroup.org/onlinepubs/9699919799/functions/fclose.html

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))




#define LOOP1(a) char[1]: ARRAY_LENGTH(array),
#define LOOP2(a) char[2]: ARRAY_LENGTH(array), LOOP1()
#define LOOP3(a) char[3]: ARRAY_LENGTH(array), LOOP2()

//#define LOOPN(n) LOOP##n




//// TODO this requires c11; are you ok with that?
//// TODO this doesn't actually check for other pointer types? 
//// TODO handle unsupported types: https://iifx.dev/en/articles/460125220/generic-macro-hacking-achieving-type-safety-and-custom-error-messages-in-c
#define LENGTH(array) _Generic(array, \
	char[35]: ARRAY_LENGTH(array), \
	char[]: ARRAY_LENGTH(array) \
)



// https://sgf4.github.io/posts/foreach-macro/
// https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/recommendations/preprocessor-pre/pre10-c/

#define DO_THING printf("Shake it, Baby\n")
#define DO_THING_2 DO_THING; DO_THING
#define DO_THING_4 DO_THING_2; DO_THING_2
#define DO_THING_8 DO_THING_4; DO_THING_4
#define DO_THING_16 DO_THING_8; DO_THING_8


#define DO_THING_N(N, array) \
	if(((N)&1)==0){char[0]: ARRAY_LENGTH(array)}\
    if(((N)&1)!=0){char[N]: ARRAY_LENGTH(array), DO_THING_N(N - 1, array)} // this leverages the compiler optimizing away dead code...



// http://www.individual.utoronto.ca/dfr/hmmmm/2020/07/26/1.html


#define EMPTY()
#define DEFER(m) m EMPTY()
#define EVAL(m) m

#define FOR_EACH_() FOR_EACH

#define PRINT_DOUBLE(b, a) printf(#a #b "\n");
#define PRINT_DOUBLE_HELPER(a) DEFER(FOR_EACH_)()(PRINT_DOUBLE, a)









// http://jhnet.co.uk/articles/cpp_magic

//// TODO this one seems like it might work eventually; you are at `#define DEFER1(m) m EMPTY()`




#define FIRST(a, ...) a
#define SECOND(a, b, ...) b

#define EMPTY()

#define EVAL1(...) __VA_ARGS__
#define EVAL2(...) EVAL1(EVAL1(__VA_ARGS__))
#define EVAL4(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL8(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL16(...) EVAL8(EVAL8(__VA_ARGS__))
#define EVAL32(...) EVAL16(EVAL16(__VA_ARGS__))
#define EVAL64(...) EVAL32(EVAL32(__VA_ARGS__))
#define EVAL128(...) EVAL64(EVAL64(__VA_ARGS__))
#define EVAL256(...) EVAL128(EVAL128(__VA_ARGS__))
#define EVAL512(...) EVAL256(EVAL256(__VA_ARGS__))
#define EVAL1024(...) EVAL512(EVAL512(__VA_ARGS__))
#define EVAL(...) EVAL1024(__VA_ARGS__)

#define DEFER1(m) m EMPTY()
#define DEFER2(m) m EMPTY EMPTY()()
#define DEFER3(m) m EMPTY EMPTY EMPTY()()()
#define DEFER4(m) m EMPTY EMPTY EMPTY EMPTY()()()()

#define IS_PROBE(...) SECOND(__VA_ARGS__, 0)
#define PROBE() ~, 1

#define CAT(a,b) a ## b

#define NOT(x) IS_PROBE(CAT(_NOT_, x))
#define _NOT_0 PROBE()

#define BOOL(x) NOT(NOT(x))

#define IF_ELSE(condition) _IF_ELSE(BOOL(condition))
#define _IF_ELSE(condition) CAT(_IF_, condition)

#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE

#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

#define HAS_ARGS(...) BOOL(FIRST(_END_OF_ARGUMENTS_ __VA_ARGS__)())
#define _END_OF_ARGUMENTS_() 0

#define MAP(m, first, ...)           \
  m(first)                           \
  IF_ELSE(HAS_ARGS(__VA_ARGS__))(    \
    DEFER2(_MAP)()(m, __VA_ARGS__)   \
  )(                                 \
    /* Do nothing, just terminate */ \
  )
#define _MAP() MAP

#define GREET(x) Hello, x!





/*#define NATURALS_0 0
#define NATURALS_1 1, NATURALS_0
#define NATURALS_2 2, NATURALS_1
#define NATURALS_3 3, NATURALS_2
#define NATURALS_4 4, NATURALS_3
#define NATURALS_5 5, NATURALS_4
#define NATURALS_6 6, NATURALS_5
#define NATURALS_7 7, NATURALS_6



#define _THE_PATTERN(n) char[n]: ARRAY_LENGTH(array) 
#define THE_PATTERN(n) IF_ELSE(n)(_THE_PATTERN(n), )()*/

//#define PATTERNS(n) \
//	IF_ELSE(n)

//#define _PATTERNS() PATTERNS






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







enum mainError main()
{
	////THE_PATTERN(4);

	EVAL(MAP(GREET, Mum, Dad, Adam, Joe))



	char path2[] = "c:\\users\\ravud\\test\\test2\\test.tx";
	if (0)
	{
		int length = LENGTH(path2);
	}
	else
	{
		int length = LENGTH(path2);
	}

	//EVAL1(A EMPTY() (123))


	//EVAL(FOR_EACH(PRINT_DOUBLE_HELPER))



	//// TODO put array length macro in its own file (a private include header)
	//// TODO make sure you still have the spacing correct in this file (compare it to your other files)
	//// TODO some of your error codes aren't actually possible (for example, EINVAL in the `writeToFile` can't come from `fopen`)
	//// TODO write a unit test to confirm that the file was written
	//// TODO go through TODOs

	enum mainError returnValue = SUCCESS;
	int error;

	char path[] = "c:\\users\\ravud\\test\\test2\\test.txt";
	error = writeToFilePath(path, LENGTH(path), "contents");
	if (error != SUCCESS)
	{
		switch (error)
		{
		case writeToFilePathError_EACCES:
			returnValue = mainError_EACCES;
			break;
		case writeToFilePathError_OPEN_EINTR:
			returnValue = mainError_OPEN_EINTR;
			break;
		case writeToFilePathError_EISDIR:
			returnValue = mainError_EISDIR;
			break;
		case writeToFilePathError_ELOOP:
			returnValue = mainError_ELOOP;
			break;
		case writeToFilePathError_EMFILE:
			returnValue = mainError_EMFILE;
			break;
		case writeToFilePathError_ENAMETOOLONG:
			returnValue = mainError_ENAMETOOLONG;
			break;
		case writeToFilePathError_ENOSPC:
			returnValue = mainError_ENOSPC;
			break;
		case writeToFilePathError_ENOTDIR:
			returnValue = mainError_ENOTDIR;
			break;
		case writeToFilePathError_ENXIO:
			returnValue = mainError_ENXIO;
			break;
		case writeToFilePathError_OPEN_EOVERFLOW:
			returnValue = mainError_OPEN_EOVERFLOW;
			break;
		case writeToFilePathError_EROFS:
			returnValue = mainError_EROFS;
			break;
		case writeToFilePathError_EINVAL:
			returnValue = mainError_EINVAL;
			break;
		case writeToFilePathError_ENOMEM:
			returnValue = mainError_ENOMEM;
			break;
		case writeToFilePathError_ETXTBSY:
			returnValue = mainError_ETXTBSY;
			break;
		case writeToFilePathError_EAGAIN:
			returnValue = mainError_EAGAIN;
			break;
		case writeToFilePathError_EFBIG:
			returnValue = mainError_EFBIG;
			break;
		case writeToFilePathError_PRINT_EINTR:
			returnValue = mainError_PRINT_EINTR;
			break;
		case writeToFilePathError_EIO:
			returnValue = mainError_EIO;
			break;
		case writeToFilePathError_EPIPE:
			returnValue = mainError_EPIPE;
			break;
		case writeToFilePathError_EILSEQ:
			returnValue = mainError_EILSEQ;
			break;
		case writeToFilePathError_PRINT_EOVERFLOW:
			returnValue = mainError_PRINT_EOVERFLOW;
			break;
		case writeToFilePathError_CLOSE_EAGAIN:
			returnValue = mainError_CLOSE_EAGAIN;
			break;
		case writeToFilePathError_CLOSE_EFBIG:
			returnValue = mainError_CLOSE_EFBIG;
			break;
		case writeToFilePathError_CLOSE_EINTR:
			returnValue = mainError_CLOSE_EINTR;
			break;
		case writeToFilePathError_CLOSE_EIO:
			returnValue = mainError_CLOSE_EIO;
			break;
		case writeToFilePathError_CLOSE_ENOMEM:
			returnValue = mainError_CLOSE_ENOMEM;
			break;
		case writeToFilePathError_CLOSE_ENOSPC:
			returnValue = mainError_CLOSE_ENOSPC;
			break;
		case writeToFilePathError_CLOSE_EPIPE:
			returnValue = mainError_CLOSE_EPIPE;
			break;
		case writeToFilePathError_CLOSE_ENXIO:
			returnValue = mainError_CLOSE_ENXIO;
			break;
		default:
			returnValue = mainError_BUG;
			break;
		}

		goto catch;
	}

	finally:
	printf("press any key to continue");
	int c = fgetc(stdin);
	return returnValue;

	catch:
	printf("ERROR! %d", returnValue);
	goto finally;
}