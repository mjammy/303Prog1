#ifndef SUPPORT_H__
#define SUPPORT_H__

/* Store information about the team who completed the assignment, to
 * simplify the grading process.  This is just a declaration.  The definition
 * is in team.c. */
extern struct team_t
{
	char *name1;
	char *email1;
	char *name2;
	char *email2;
	char *name3;
	char *email3;
} team;

/* This function verifies that the team name is filled out */
void check_team(char *);

#endif // SUPPORT_H__
