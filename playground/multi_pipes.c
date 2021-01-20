#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
// #include <errno.h>
// #include <signal.h>

int main(void)
{
	char *argv[] = {"ls", "|", "head", "|", "wc", NULL};
	int	i;
	int pipe_locate[10];
	int	pipe_count;

	pipe_count = 0;
	pipe_locate[0] = -1;
	for (i = 0; argv[i] != NULL; i++)
	{
		if (strcmp(argv[i], "|") == 0)
		{
			pipe_count++;
			pipe_locate[pipe_count] = i;
			argv[i] = NULL;
		}
	}

	int pfd[9][2];
	if (pipe_count == 0)
	{
		if (fork() == 0)
		{
			execvp(argv[0], argv);
			exit(EXIT_SUCCESS);
		}
		else
		{
			int status;
			wait(&status);
		}
	}
	for (i = 0; i < pipe_count + 1 && pipe_count != 0; i++)
	{
		if (i != pipe_count)
			pipe(pfd[i]);
		if (fork() == 0)
		{
			if (i == 0)
			{
				dup2(pfd[i][1], 1);
			}
		}
	}
}
