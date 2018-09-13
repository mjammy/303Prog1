#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"support.h"

/* Make sure that the student names and email fields are not empty. */
void check_team(char * progname)
{
	if((strcmp("", team.name1) == 0) || (strcmp("", team.email1) == 0))
	{
		printf("%s: Please fill in the team struct in team.c\n", progname);
		exit(1);
	}
	if((strcmp("", team.name2) == 0) || (strcmp("", team.email2) == 0))
	{
		printf("%s: Please fill in the team struct in team.c\n", progname);
		exit(1);
	}
	if((strcmp("", team.name3) == 0) || (strcmp("", team.email3) == 0))
	{
		printf("%s: Please fill in the team struct in team.c\n", progname);
		exit(1);
	}
	printf("Student 1 : %s\n", team.name1);
	printf("Email 1   : %s\n", team.email1);
	printf("Student 2 : %s\n", team.name2);
	printf("Email 2   : %s\n", team.email2);
	printf("Student 3 : %s\n", team.name3);
	printf("Email 3   : %s\n", team.email3);
	printf("\n");
}
