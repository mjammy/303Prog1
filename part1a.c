#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"support.h"

/* help() - Print a help message. */
void help(char *progname)
{
	printf("Usage: %s\n", progname);
	printf("(This is just a demonstration of the traditional way\n");
	printf(" to use .so files)\n");
}

/* declare the hello() function that lives in a shared library */
extern void *hello(void* param);

/* main() - The main routine parses arguments and invokes hello */
int main(int argc, char **argv)
{
	/* for getopt */
	long opt;

	/* run a student name check */
	check_team(argv[0]);

	/* parse the command-line options. For this program, we only support */
	/* the parameterless 'h' option, for getting help on program usage.  */
	while((opt = getopt(argc, argv, "h")) != -1)
	{
		switch(opt)
		{
		case 'h': 	help(argv[0]); 	break;
		}
	}

	hello(NULL);

	/* TODO: execute the new function "ucase" that you added to libpart1.c */

	return 0;
}
