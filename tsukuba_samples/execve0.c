#include <unistd.h>

extern char **environ;

int main(void)
{
        char *argv[3];

        argv[0] = "/bin/ls";
        argv[1] = "/";
		argv[2] = NULL; 	

        execve(argv[0], argv, environ);

        return 0;
}
