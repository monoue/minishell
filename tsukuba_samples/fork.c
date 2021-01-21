#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
    
void do_child(void)
{
        printf("This is child(pid=%d).\n", getpid());
        exit(2);
}
    
int main(void)
{
        int child, status;
    
        if ((child = fork()) < 0)
		{
			perror("fork");
			exit(1);
        }
        if (child == 0)
                do_child();
		else
		{
			if (wait(&status) < 0)
			{
					perror("wait");
					exit(1);
			}
			printf("The child (pid=%d) exited with status(%d).\n", child, WEXITSTATUS(status));
        }

        return 0;
}
