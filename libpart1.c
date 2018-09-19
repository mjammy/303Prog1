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

void *ucase(void *input) {

	// Cast void pointer to struct pointer

	struct team_t *input_team = (struct team_t *)input;
	struct team_t *upper_team = malloc(sizeof(struct team_t));

	// copy the fields of the parameter struct to the fields of the new team struct
	upper_team->name1 = malloc(sizeof(input_team->name2));
	upper_team->email1 = malloc(sizeof(input_team->email2));
	upper_team->name2 = malloc(sizeof(input_team->name2));
	upper_team->email2 = malloc(sizeof(input_team->email2));


	// capitalize name1
	int i = 0;
	while(input_team->name1[i]){
		upper_team->name1[i] = toupper(input_team->name1[i]);
		i++;
	}

	// capitalize email1
	int j = 0;
	while(input_team->email1[j]){
		upper_team->email1[j] = toupper(input_team->email1[j]);
		j++;
	}

	// capitalize name2
	int k = 0;
	while(input_team->name2[k]){
		upper_team->name2[k] = toupper(input_team->name2[k]);
		k++;
	}

	// capitalize email2
	int l = 0;
	while(input_team->email2[l]){
		upper_team->email2[l] = toupper(input_team->email2[l]);
		l++;
	}

	printf("Student 1 : %s\n", upper_team->name1);
	printf("Email 1 : %s\n", upper_team->email1);
	printf("Student 2 : %s\n", upper_team->name2);
	printf("Email 2 : %s\n", upper_team->email2);

	return NULL;
}
