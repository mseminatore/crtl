//-------------------------------------------------------------------------------
// Copyright 2022 Mark Seminatore. All rights reserved.
//-------------------------------------------------------------------------------

#include "config.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "unistd.h"
#include "errno.h"

// TODO - update for non ARM64 arch
#if defined(__aarch64__)
    typedef long INT;
#else
    typedef int INT;
#endif

#if defined(_WIN32)
	#pragma warning (disable : 4996)
	#define _CRT_SECURE_NO_WARNINGS
	#include <Windows.h>
	// TODO - do we need to AllocConsole() or AttachConsole() on startup?
	#include <fcntl.h>
	#include <io.h>
	#include <sys/stat.h>

	#define RWX (S_IWRITE | S_IREAD)
#else
	#include <sys/syscall.h>
	#include "unistd.h"

	#define RWX S_IRWXU
#endif

#include "stdarg.h"

// floating point support is not yet implemented, 
// but we need to define this for the vsprintf implementation
#if defined(CRTL_INC_FLOAT)
	typedef struct _FLOAT
	{
		unsigned long long sign : 1;
		unsigned long long exp : 11;
		unsigned long long mant : 52;
	} _FLOAT;

	union FLOAT
	{
		_FLOAT f;
		double d;
	};
#endif

static char __cwd[FILENAME_MAX] = "." DIR_MARKER;

// standard IO handles
FILE _stdin		= { 0, 0, 0 },	*stdin = &_stdin;
FILE _stdout	= { 0, 1 ,0 },	*stdout = &_stdout;
FILE _stderr	= { 0, 2, 0 },	*stderr = &_stderr;

// INT openFiles = 0;

// free list for FILE structures
// static FILE freeList[FOPEN_MAX] = { 0 };
// static int freeListIndex = 0;

//---------------------------------------------
// Sends a character to stdout.
//---------------------------------------------
int putchar(int c)
{
	return putc(c, stdout);
}

//----------------------------------------------
// Sends a character to the given stream.
// TODO - this should be a macro that calls fputc
//----------------------------------------------
int putc(int chr, FILE *stream)
{
	return fputc(chr, stream);
}

//-----------------------------------------------
// Sends a character to the given stream.
//-----------------------------------------------
int fputc(int chr, FILE *stream)
{
	assert(stream);
	if (!stream)
	{
		errno = EINVAL;
		return EOF;
	}
	
	if (1 != write(stream->fildes, &chr, 1))
	{
		return EOF;
	}

	return 1;
}

//-----------------------------------------------
// Sends a string to the given stream.
//-----------------------------------------------
int fputs(const char *str, FILE *stream)
{
	assert(str && stream);
	if (!str || !stream)
	{
		errno = EINVAL;
		return EOF;
	}

	return write(stream->fildes, str, strlen(str));
}

//-----------------------------------------------
// Sends a string to stdout.
//-----------------------------------------------
int puts(const char *str)
{
	assert(str);
	if (!str)
	{
		errno = EINVAL;
		return EOF;
	}

	int len = strlen(str);

#if defined(_WIN32)
	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (stdOut != NULL && stdOut != INVALID_HANDLE_VALUE)
	{
		DWORD written = 0;

		// If GetStdHandle or WriteConsole return false, then you may need to use AllocConsole().
		WriteConsoleA(stdOut, str, len, &written, NULL);
	}
#endif

#if defined(__APPLE_CC__)
	int result = write(STDOUT_FILENO, str, len);
	if (result != len)
		return EOF;

	write(STDOUT_FILENO, "\n", 1);
#endif

	return 1;
}

//-----------------------------------------------
// Opens the filename pointed to by filename using the given mode.
//-----------------------------------------------
FILE *fopen(const char *filename, const char *mode)
{
	assert(filename && mode);
	if (!filename || ! mode)
	{
		errno = EINVAL;
		return NULL;
	}

	// process mode argument
	int flags = 0;
	if (strchr(mode, 'r'))
		flags |= O_RDONLY;

	if (strchr(mode, 'w'))
		flags |= (O_WRONLY | O_CREAT | O_TRUNC);

	if (strchr(mode, 'a'))
		flags |= (O_WRONLY | O_CREAT | O_APPEND);

	mode_t omode = 0;

	if (flags & O_CREAT)
		omode = RWX;

	int fd = open(filename, flags, omode);
	if (fd < 0)
	{
		errno = ENOENT;
		return NULL;
	}

	// alloc FILE structure
	// TODO - replace with static array alloc
	FILE *stream = (FILE*)malloc(sizeof(FILE));
	assert(stream);
	if (!stream)
	{
		errno = ENOMEM;
		return NULL;
	}

	stream->fildes	= fd;
	stream->pos		= 0;
	stream->status	= 0;

	return stream;
}

//-----------------------------------------------
// Closes the given stream and disassociates it from any file.
//-----------------------------------------------
int fclose(FILE *stream)
{
	assert(stream);
	if (!stream)
	{
		errno = EINVAL;
		return EOF;
	}

	int result = close(stream->fildes);
	stream->fildes	= -1;
	stream->status	= EOF;
	stream->pos		= -1;

	// free FILE structure
	// TODO - return to free list instead of actually freeing
	free(stream);

	return result;
}

//-----------------------------------------------
// Reads data from the given stream into the array pointed to by ptr.
//-----------------------------------------------
size_t fread(void *ptr, size_t size, size_t nitems, FILE *stream)
{
	assert(ptr && stream /*&& stream->status != EOF && stream->fildes != -1*/);
	if (!ptr || !stream)
	{
		errno = EINVAL;
		return 0;
	}

	int count = read(stream->fildes, ptr, nitems * size);

	// check for end of file, success, or error
	if (count == 0)
	{
		stream->status = EOF;
		return 0;
	} else if (count == nitems * size)
		return nitems;	

	errno = EIO;
	return -1;
}

//-----------------------------------------------
// Writes data from the array pointed to by ptr to the given stream.
//-----------------------------------------------
size_t fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream)
{
	assert(ptr && stream);
	if (!ptr || !stream)
	{
		errno = EINVAL;
		return 0;
	}

	int count = write(stream->fildes, ptr, nitems * size);
	if (count == nitems * size)
		return nitems;

	return 0;
}

//-----------------------------------------------
// Sends formatted output to a string using an argument list.
//-----------------------------------------------
int vsprintf(char *str, const char *format, va_list argp)
{
	int count = 0, chr;
	char *pbuf = str;

	if (!str || !format)
	{
		errno = EINVAL;
		return 0;
	}

	while ((chr = *format))
	{
		if (chr == '%')
		{
			// get format specififer
			format++;
			switch (*format)
			{
			case '%':
				*pbuf++ = '%';
				count++;
				break;

			case 'i':
			case 'd':
			{
				int ival = va_arg(argp, INT);
				char int_string[32];

				_itoa(ival, int_string, 10);
				strcpy(pbuf, int_string);
				int len = strlen(int_string);
				pbuf += len;
				count += len;
			}
			break;

			case 'f':
			{
				assert(("not yet implemented", 0));

				//union FLOAT f;

				//double val = va_arg(argp, double);
				//f.d = val;
				//printf("%c", f.f.sign);
			}
			break;

			case 'c':
			{
				*pbuf++ = va_arg(argp, INT);
				count++;
			}
			break;

			case 's':
			{
				char *pstr = va_arg(argp, char*);

				strcpy(pbuf, pstr);
				int len = strlen(pstr);
				pbuf += len;
				count += len;
			}
			break;

			default:
				assert(0);
				return -1;
			}
		}
		else
		{
			*pbuf++ = chr;
			count++;
		}

		format++;
	}

	*pbuf = 0;	// make sure we are asciiz

	return count;
}

//-----------------------------------------------
// Sends formatted output to a string.
//-----------------------------------------------
int sprintf(char *str, const char *format, ...)
{
	int count;

	va_list argp;

	assert(str && format);
	if (!str || !format)
	{
		errno = EINVAL;
		return 0;
	}

	va_start(argp, format);
		count = vsprintf(str, format, argp);
	va_end(argp);

	return count;
}

//-----------------------------------------------
// Sends formatted output to a stream using an argument list.
//-----------------------------------------------
int vfprintf(FILE *stream, const char *format, va_list argp)
{
	int count;
	char buf[CRTL_PRINTF_MAX];

	assert(stream && format);
	if (!stream || !format)
	{
		errno = EINVAL;
		return 0;
	}

	count = vsprintf(buf, format, argp);

	fputs(buf, stream);

	return count;
}

//-----------------------------------------------
// Sends formatted output to a stream.
//-----------------------------------------------
int fprintf(FILE *stream, const char *format, ...)
{
	int count;
	va_list argp;

	assert(stream && format);
	if (!stream || !format)
	{
		errno = EINVAL;
		return 0;
	}

	va_start(argp, format);
		count = vfprintf(stream, format, argp);
	va_end(argp);

	return count;
}

//-----------------------------------------------
// Sends formatted output to stdout using an argument list.
//-----------------------------------------------
int vprintf(const char *format, va_list argp)
{
	return vfprintf(stdout, format, argp);
}

//-----------------------------------------------
// Sends formatted output to stdout.
//-----------------------------------------------
int printf(const char *format, ...)
{
	int count;
	va_list argp;

	assert(format);
	if (!format)
	{
		errno = EINVAL;
		return 0;
	}

	va_start(argp, format);
		count = vprintf(format, argp);
	va_end(argp);

	return count;
}

//-----------------------------------------------
// Deletes the file specified by filename.
//-----------------------------------------------
int remove(const char *filename)
{
	assert(filename);
	if (!filename)
	{
		errno = EINVAL;
		return -1;
	}

	return unlink(filename);
}

//-----------------------------------------------
// Reads the next character from the given stream 
// and returns it as an unsigned char cast to an 
// int, or EOF on end of file or error.
//-----------------------------------------------
int fgetc(FILE *stream)
{
	int chr;

	assert(stream);
	if (!stream)
	{
		errno = EINVAL;
		return EOF;
	}

	int count = read(stream->fildes, &chr, 1);
	if (count == 0)
	{
		stream->status = EOF;
		return EOF;
	}
	else if (count != 1)
	{
		errno = EIO;
		return EOF;
	}

	return chr;
}

//-----------------------------------------------
// Reads a line from the specified stream and 
// stores it into the string pointed to by str. 
// It stops when either (n-1) characters are read, 
// the newline character is read, or the end-of-file
// is reached, whichever comes first.
//-----------------------------------------------
char *fgets(char *str, int n, FILE *stream)
{
	assert(str && stream);
	if (!str || !stream)
	{
		errno = EINVAL;
		return NULL;
	}

	for (int i = 0; i < n - 1; i++)
	{
		int chr = fgetc(stream);
		if (chr == EOF)
		{
			if (i == 0)
			{
				return NULL;
			}
			else
			{				
				str[i] = 0;		// make sure we are asciiz
				return str;
			}
		}
		str[i] = chr;

		if (chr == '\n')
		{
			str[i + 1] = 0;
			return str;
		}
	}

	str[n - 1] = 0;	// make sure we are asciiz

	return str;
}

//-----------------------------------------------
// Reads the next character from stdin and returns 
// it as an unsigned char cast to an int, or EOF 
// on end of file or error.
//-----------------------------------------------
int getc(FILE *stream)
{
	assert(stream);
	if (!stream)
	{
		errno = EINVAL;
		return EOF;
	}

	return fgetc(stream);
}

//-----------------------------------------------
// Reads the next character from stdin and returns 
// it as an unsigned char cast to an int, or EOF 
//on end of file or error.
//-----------------------------------------------
int getchar(void)
{
	return fgetc(stdin);
}

//-----------------------------------------------
// Reads a line from stdin and stores it into the 
// string pointed to by, str. It stops when either 
// the newline character is read or when the 
// end-of-file is reached, whichever comes first.
//-----------------------------------------------
char *gets(char *str)
{
	assert(str);

	return fgets(str, BUFSIZ, stdin);
}

//-----------------------------------------------
// Pushes the character specified by chr (converted
// to an unsigned char) back onto the input stream
// pointed to by stream. The character is returned
// as an unsigned char cast to an int, or EOF 
// on error.
//-----------------------------------------------
int ungetc(int chr, FILE *stream)
{
	assert(stream);
	if (!stream)
	{
		errno = EINVAL;
		return EOF;
	}
}

//-----------------------------------------------
// Converts the integer value to a null-terminated 
// string using the specified base and stores the
// result in the array given by str. The base
// argument is used to specify the base to which the
// integer value is converted, and must be between
// 2 and 36 inclusive. The resulting string is 
// null-terminated and returned in str. If the base
// is 10 and value is negative, the resulting string
// is preceded with a minus sign (-). No other base
// produces a string with a sign character
//-----------------------------------------------
char *_itoa(int value, char *str, int base)
{
	char *pchr = str;
	int place_value;

	// check for negative numbers
	if (value < 0 && base == 10)
		*pchr++ = '-';

	if (value == 0)
		*pchr++ = '0';

	while (value)
	{
		place_value = value % base;

		*pchr++ = place_value + '0';
		value /= base;
	}

	*pchr = 0;	// make sure we are asciiz!

	return _strrev(str);
}

//-----------------------------------------------
// Checks the end-of-file indicator for the given stream.
// Returns a non-zero value if the end of the file has
// been reached, otherwise returns 0.
//-----------------------------------------------
int feof(FILE *stream)
{
	assert(stream);
	if (!stream)
	{
		errno = EINVAL;
		return EOF;
	}

	if (stream->status == EOF)
		return 1;

	return 0;
}

//-----------------------------------------------
// Clears the error indicator for the given stream.
//-----------------------------------------------
void clearerr(FILE *stream)
{
	assert(stream);
	if (!stream)
	{
		errno = EINVAL;
		return;
	}

	// TODO - this should probably also reset the file position to the beginning of the file?
	stream->status = 0;
}

//-----------------------------------------------
// Checks the error indicator for the given stream.
// Returns a non-zero value if the error indicator 
// is set for the stream, otherwise returns 0.
//-----------------------------------------------
int ferror(FILE *stream)
{
	assert(stream);
	if (!stream)
	{
		errno = EINVAL;
		return EOF;
	}

	if (stream->status != 0)
		return 1;

	return 0;
}

//-----------------------------------------------
// Flushes the output buffer of a stream. If the 
// stream argument is NULL, the fflush() function 
// flushes all open output streams.
//-----------------------------------------------
int fflush(FILE *stream)
{
	assert(stream);
	if (!stream)
	{
		errno = EINVAL;
		return EOF;
	}

	// TODO - this should probably also flush any buffers we have in memory to the file

	return 0;
}

//-----------------------------------------------
// Sets the file position of the given stream to the
// given offset according to the directive whence.
//-----------------------------------------------
int fseek(FILE *stream, long offset, int whence)
{
	assert(stream);
	if (!stream)
	{
		stream->status = EOF;
		errno = EINVAL;
		return EOF;
	}

	// lseek returns the resulting absolute offset; use it to update pos
	long new_pos = (long)syscall(SYS_lseek, stream->fildes, offset, whence);
	if (new_pos < 0)
	{
		stream->status = EOF;
		return EOF;
	}

	stream->pos = (fpos_t)new_pos;
	return 0;
}

//-----------------------------------------------
// Returns the current file position of the given
// stream. On success, ftell() returns the current 
// file position of the given stream. The file 
// position is the number of bytes from the 
// beginning of the file. On error, ftell() returns
// EOF and sets the error indicator on the stream.
//-----------------------------------------------
long ftell(FILE *stream)
{
	assert(stream);
	if (!stream)
	{
		stream->status = EOF;
		errno = EINVAL;
		return EOF;
	}

	// query the kernel for the actual current position (handles reads/writes
	// that may have advanced the file pointer without updating stream->pos)
	long pos = (long)syscall(SYS_lseek, stream->fildes, 0, SEEK_CUR);
	if (pos < 0)
	{
		stream->status = EOF;
		return EOF;
	}

	stream->pos = (fpos_t)pos;
	return pos;
}

//-----------------------------------------------
// Sets the file position to the beginning of the
// file for the given stream.
//-----------------------------------------------
void rewind(FILE *stream)
{
	assert(stream);
	if (!stream)
	{
		errno = EINVAL;
		return;
	}

	// reset the file position to the beginning of the file
	syscall(SYS_lseek, stream->fildes, 0, SEEK_SET);
	stream->pos = 0;
	stream->status = 0;
}

//-----------------------------------------------
// Changes the name of the file specified by oldname to newname.
//-----------------------------------------------
int rename(const char *oldname, const char *newname)
{
	assert(oldname && newname);
	if (!oldname || !newname)
	{
		errno = EINVAL;
		return EOF;
	}

	return _rename(oldname, newname);
}

//-----------------------------------------------
// Prints a descriptive error message to stderr. 
// The argument str is a string that is included 
// in the output to identify the source of the 
// error. The message written to stderr consists 
// of the string pointed to by str, followed by
// a colon and a space, followed by the error 
// message corresponding to the current value 
// of errno, and a newline character.
//-----------------------------------------------
void perror(const char *str)
{
	assert(str);
	if (!str)
	{
		errno = EINVAL;
		return;
	}

	fprintf(stderr, "%s: %s\n", str, strerror(errno));
}
