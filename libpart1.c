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
<<<<<<< HEAD

void *ucase(char *progname) {

	// Allocate a new team struct
	struct team_t newTeam;

	// copy the fields of the parameter struct to the fields of the new team struct
	newTeam.name1 = team.name1;
	newTeam.email1 = team.email1;
	newTeam.name2 = team.name2;
	newTeam.email2 = team.email2;
	newTeam.name3 = team.name3;
	newTeam.email3 = team.email3;

	// uppercase those fields
	char *s;

	s = newTeam.name1;
	while (*s) {
		*s = toupper((unsigned char) *s);
		s++;
	}
	newTeam.name1 = s;

	s = newTeam.email1;
	while (*s) {
		*s = toupper((unsigned char) *s);
		s++;
	}
	newTeam.email1 = s;

	s = newTeam.name2;
	while (*s) {
		*s = toupper((unsigned char) *s);
		s++;
	}
	newTeam.name2 = s;

	s = newTeam.email2;
	while (*s) {
		*s = toupper((unsigned char) *s);
		s++;
	}
	newTeam.email2 = s;

	s = newTeam.name3;
	while (*s) {
		*s = toupper((unsigned char) *s);
		s++;
	}
	newTeam.name3 = s;

	s = newTeam.email3;
	while (*s) {
		*s = toupper((unsigned char) *s);
		s++;
	}
	newTeam.email3 = s;

	return &newTeam;
}
=======
>>>>>>> ac03c2e238057fd7eb3bd63c42069413f24da756
