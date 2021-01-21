#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[])
{
        pid_t pid;

        if (argc != 2) {
                fprintf(stderr, "Usage: %s pid\n", argv[0]);
                exit(1);
        }

        pid = atoi(argv[1]);

        if (pid <= 0) {
                fprintf(stderr, "Invalid pid: %d\n", pid);
                exit(1);
        }

        if (kill(pid, SIGINT) < 0) {
                perror("kill");
                exit(1);
        }

        return 0;
}
