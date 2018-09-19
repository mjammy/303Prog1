#include<stdint.h>
#include<stdio.h>
#include<dlfcn.h>
#include<string.h>
#include<errno.h>
#include<execinfo.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdarg.h>

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

int fscanf(FILE *stream, const char *format, ...) {

 	fprintf(stderr, "yoyoyyo");
    static int (*origFscanf)(FILE*, const char*, ...) = NULL;
	char *error;

	// saves function call for later
	origFscanf = dlsym(RTLD_NEXT, "fscanf");

	// does variadic function behavior
	va_list ap;
    va_start(ap, format);

	char* password = "turtlemsj219"; // <- this is the only part that needs to be changed I'm pretty sure. 
									 // instead of "msj219", we need to somehow programmatically put in the userlogin

	FILE* passFile = fmemopen(password, sizeof(password), "r");
    int rc = vfscanf(passFile, format, ap);
	va_end(ap);
    return rc;
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

