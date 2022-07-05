// Copyright 2022 Mark Seminatore. All rights reserved.
#ifndef __STDIO_H
#define __STDIO_H

typedef unsigned long fpos_t;

typedef struct
{
	int status;
	int fildes;
	fpos_t pos;
} FILE;

// standard IO handles
#define stdin 0
#define stdout 1
#define stderr 2

#define BUFSIZ 4096

#define FOPEN_MAX 256
#define FILENAME_MAX 256

#ifndef EOF
#	define EOF -1
#endif

int puts(const char *str);
int printf(const char *format, ...);
int putchar(int c);
int fprintf(FILE *stream, const char *format, ...);

int fclose(FILE *stream);
int feof(FILE *stream);
FILE *fopen(const char *filename, const char *mode);
//size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
//size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int remove(const char *filename);
int fgetc(FILE *stream);
char *fgets(char *str, int n, FILE *stream);
int fputc(int chr, FILE *stream);
int fputs(const char *str, FILE *stream);
int getc(FILE *stream);
int getchar(void);
char *gets(char *str);
int putc(int chr, FILE *stream);
int ungetc(int chr, FILE *stream);

#endif	//__STDIO_H