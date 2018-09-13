#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"support.h"

/* hello() - print some output so we know the shared object loaded.
 *
 * The function signature takes an untyped parameter, and returns an untyped
 * parameter. In this way, the signature *could* support any behavior, by
 * passing in a struct and returning a struct. */
void *hello(void *input)
{
	printf("hello from a .so\n");
	return NULL;
}

