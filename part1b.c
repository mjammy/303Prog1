#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <dlfcn.h>
#include"support.h"


/* load_and_invoke() - load the given .so and execute the specified function */
void load_and_invoke(char *libname, char *funcname)
{
	// https://linux.die.net/man/3/dlsym
	// https://stackoverflow.com/questions/1354537/dlsym-dlopen-with-runtime-arguments
	// https://gist.github.com/yellowbyte/ec470d75ba7c14ebefed271c6fe58e9e

	/* TODO: complete this function */
	typedef void* (*func_ptr_t)(void*);

	void *handle;
	char *error;

	// this all came from the linux man page
	handle = dlopen(libname, RTLD_LAZY | RTLD_GLOBAL);
	if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

	// this all came from the linux man page
	dlerror();    /* Clear any existing error */

	// this all came from the linux man page
	func_ptr_t fptr = (func_ptr_t)dlsym(handle, funcname);

	// this all came from the linux man page
	if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
	}

	// run function
	fptr(NULL);

	// this all came from the linux man page
	dlclose(handle);

	exit(EXIT_SUCCESS);

}

/* help() - Print a help message. */
void help(char *progname)
{
	printf("Usage: %s [OPTIONS]\n", progname);
	printf("Load the given .so and run the requested function from that .so\n");
	printf("  -l [string] The name of the .so to load\n");
	printf("  -f [string] The name of the function within that .so to run\n");
}

/* main() - The main routine parses arguments and invokes hello */
int main(int argc, char **argv)
{
	/* for getopt */
	long opt;

	/* run a student name check */
	check_team(argv[0]);


	//	MUSA commented this command line options part out
	//  We can worry about implementing the args when it works
	//
	/* parse the command-line options. For this program, we only support */
	/* the parameterless 'h' option, for getting help on program usage.  */
/* 	while((opt = getopt(argc, argv, "h")) != -1)
	{
		switch(opt)
		{
		case 'h':	help(argv[0]); 	break;
		}
	} */

	/* call load_and_invoke() to run the given function of the given library */
	// this has my path, couldn't figure out how to fix it without that
	// NOTE: I'm using the void test() function, which I declared in libpart1.c
	load_and_invoke("/home/msj219/cse303/cse303.p1/obj64/libpart1.so", "hello");

	exit(0);
}

