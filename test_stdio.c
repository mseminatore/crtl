// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "errno.h"

#if defined(_WIN32)
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>
#else
#include "unistd.h"
#endif

#include "testy/test.h"

//
static void test_puts()
{
	SUITE("puts");

	TEST(1 == puts("Hello"));
}

//
static void test_open()
{
	char str[] = "Hello there!\n";
	int len = strlen(str);

	SUITE("open");

#if defined(_WIN32)
	int fd = open("./a.txt", O_CREAT | O_WRONLY, S_IWRITE | S_IREAD);
#else
	int fd = open("./a.txt", O_CREAT | O_WRONLY, S_IRWXU);
#endif

	TEST(fd > 0);
	TEST(len == write(fd, str, len));

	close(fd);
	remove("./a.txt");
}

//
static void test_fputs()
{
	SUITE("fputs");

	TEST(fputs("Hello!", stdout));
}

//
static void test_sprintf()
{
	char str[256];

	SUITE("sprintf");

	sprintf(str, "Hi %s, is it %d o'clock yet%c%c", "there", 1, '?', '!');

	TEST(0 == strcmp("Hi there, is it 1 o'clock yet?!", str));
}

//
static void test_fprintf()
{
	SUITE("fprintf");

	int result = fprintf(stdout, "%s", "Hello");
	TEST(5 == result);
}

//
static void test_fwrite()
{
	SUITE("fwrite");

	FILE *f = fopen("./write_test.txt", "wt");

	TEST(f != NULL);

	char str[] = "Hello there!";

	TEST(1 == fwrite(str, strlen(str), 1, f));
	fclose(f);
}

//
static void test_fread()
{
	SUITE("fread");

	FILE *f = fopen("./write_test.txt", "rt");

	TEST(f != NULL);

	char str[] = "Hello there!";
	char buf[32] = {0};

	TEST(1 == fread(buf, strlen(str), 1, f));
	TEST(0 == strcmp(str, buf));
	fclose(f);
}

//
static void test_fgets()
{
	SUITE("fgets");

	FILE *f = fopen("./write_test.txt", "rt");

	TEST(f != NULL);

	char str[] = "Hello there!";
	char buf[32] = {0};

	TEST(buf == fgets(buf, sizeof(buf), f));
	TEST(0 == strcmp(str, buf));
	fclose(f);
}

//
static void test_gets()
{
	SUITE("gets");

	char str[] = "Hello there!";
	char buf[32] = {0};

	SKIP_TEST(buf == gets(buf));
	SKIP_TEST(0 == strcmp(str, buf));
}

//
static void test_feof()
{
	SUITE("feof");

	// write a small file to read from
	FILE *f = fopen("./feof_test.txt", "wt");
	fwrite("Hi", 1, 2, f);
	fclose(f);

	f = fopen("./feof_test.txt", "rt");
	TEST(f != NULL);

	// fresh stream: not at EOF
	TEST(0 == feof(f));

	// read the two bytes, then one past end to trigger EOF
	fgetc(f);
	fgetc(f);
	fgetc(f);

	TEST(0 != feof(f));

	// clearerr resets the EOF indicator
	clearerr(f);
	TEST(0 == feof(f));

	fclose(f);
	remove("./feof_test.txt");
}

//
static void test_ferror()
{
	SUITE("ferror");

	FILE *f = fopen("./ferror_test.txt", "wt");
	fwrite("Hi", 1, 2, f);
	fclose(f);

	f = fopen("./ferror_test.txt", "rt");
	TEST(f != NULL);

	// fresh stream: no error
	TEST(0 == ferror(f));

	// read past end; status=EOF=-1, which != 0, so ferror returns non-zero
	fgetc(f);
	fgetc(f);
	fgetc(f);

	TEST(0 != ferror(f));

	// clearerr resets the error indicator
	clearerr(f);
	TEST(0 == ferror(f));

	fclose(f);
	remove("./ferror_test.txt");
}

//
static void test_clearerr()
{
	SUITE("clearerr");

	FILE *f = fopen("./clearerr_test.txt", "wt");
	fwrite("Hi", 1, 2, f);
	fclose(f);

	f = fopen("./clearerr_test.txt", "rt");
	TEST(f != NULL);

	// clearerr on a clean stream leaves it clean
	clearerr(f);
	TEST(0 == feof(f));
	TEST(0 == ferror(f));

	// read past end to set EOF, then clearerr clears both indicators
	fgetc(f);
	fgetc(f);
	fgetc(f);

	TEST(0 != feof(f));
	clearerr(f);
	TEST(0 == feof(f));
	TEST(0 == ferror(f));

	fclose(f);
	remove("./clearerr_test.txt");
}

//
static void test_remove()
{
	SUITE("remove");

	char filename[] = "write_test.txt";

	TEST(0 == remove(filename));
}

//
static void test_rename()
{
	SUITE("rename");

	// success: create a file, rename it, verify return is 0 and new name is accessible
	FILE *f = fopen("./rename_old.txt", "wt");
	TEST(f != NULL);
	fwrite("data", 1, 4, f);
	fclose(f);

	TEST(0 == rename("./rename_old.txt", "./rename_new.txt"));

	FILE *g = fopen("./rename_new.txt", "rt");
	TEST(g != NULL);
	fclose(g);
	remove("./rename_new.txt");

	// non-existent source returns non-zero
	TEST(0 != rename("./rename_does_not_exist.txt", "./rename_out.txt"));

	// NULL args trigger assert before graceful return; in NDEBUG builds assert is a no-op
	// so the graceful if-check runs and returns -1
#ifdef NDEBUG
	TEST(-1 == rename(NULL, "./rename_new.txt"));
	TEST(-1 == rename("./rename_old.txt", NULL));
#else
	SKIP_TEST(-1 == rename(NULL, "./rename_new.txt"));
	SKIP_TEST(-1 == rename("./rename_old.txt", NULL));
#endif
}

//
static void test_perror()
{
	SUITE("perror");

	// perror writes "prefix: message\n" to stderr; verify it doesn't crash
	errno = EINVAL;
	perror("test");
	TEST(1);  // reached here without crashing

	errno = 0;
	perror("no error");
	TEST(1);

	// NULL arg triggers assert; skip in debug, run in release
#ifdef NDEBUG
	perror(NULL);
	TEST(1);
#else
	SKIP_TEST(perror(NULL));
#endif
}

//
static void test_fseek()
{
	SUITE("fseek/ftell/rewind");

	// write a known file to test seeking within
	FILE *f = fopen("./fseek_test.txt", "wt");
	TEST(f != NULL);
	char content[] = "ABCDEFGHIJ";
	fwrite(content, 1, 10, f);
	fclose(f);

	f = fopen("./fseek_test.txt", "rt");
	TEST(f != NULL);

	// ftell at start should be 0
	TEST(0 == ftell(f));

	// seek to offset 3 from start
	TEST(0 == fseek(f, 3, SEEK_SET));
	TEST(3 == ftell(f));

	// read one byte — should be 'D' (4th char, index 3)
	char buf[4] = {0};
	fread(buf, 1, 1, f);
	TEST('D' == buf[0]);

	// position should now be 4
	TEST(4 == ftell(f));

	// seek 2 forward from current
	TEST(0 == fseek(f, 2, SEEK_CUR));
	TEST(6 == ftell(f));

	// rewind should reset to 0
	rewind(f);
	TEST(0 == ftell(f));

	fclose(f);
	remove("./fseek_test.txt");
}

//
// Run all stdio tests.
//
void test_stdio()
{
	test_puts();
	test_open();
	test_fputs();
	test_sprintf();
	test_fprintf();
	test_fwrite();
	test_fread();
	test_fgets();
	test_gets();
	test_feof();
	test_ferror();
	test_clearerr();
	test_remove();
	test_rename();
	test_perror();
	test_fseek();
}
