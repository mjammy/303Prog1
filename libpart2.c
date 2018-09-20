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

  //static int (*origFscanf)(FILE*, const char*, ...) = NULL;

	// saves function call for later
	//origFscanf = (int(*)(FILE*, const char*, ...))dlsym(RTLD_NEXT, "fscanf");
	//origFscanf = dlsym(RTLD_NEXT, "fscanf");

	// does variadic function behavior
	int rc;
	va_list ap;
	va_start(ap, format);

	if (strcmp(format, "%ms") == 0) {

		// Get password
		char *turtleString = "turtle";
		char *username = getlogin();

		size_t size = (strlen(username)+strlen(turtleString))*sizeof(char);
		char *password = (char*)malloc(size);
	  if ( password != NULL )
	  {
	     //strcpy(password, turtleString);
	     //strcat(password, username);

			 memcpy(password, turtleString, strlen(turtleString));
			 memcpy(password + strlen(turtleString)*sizeof(char), username, strlen(username));
			 //memcpy(password + (strlen(turtleString) + strlen(username))*sizeof(char), "\0", 2);
	  }

		FILE* passFile = fmemopen(password, strlen(password), "r");

		/*
    char * buffer = malloc(12*sizeof(char));
		fread(buffer, 1, 12, passFile);
		 //  printf("%s\n", buffer);

		fseek ( passFile , 0 , SEEK_SET );
		*/
		//printf("%s",  password, size );
  //  stream = &passFile;
		//int rc = vsscanf(password, format, ap);

	  rc = vfscanf(passFile, format, ap);
	}
	else {
		rc = vfscanf(stream, format, ap);
		va_end(ap);
	}

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
