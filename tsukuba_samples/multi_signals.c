#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sigint_count = 3;

void sigtstp_handler(int signum)
{
        printf("sigtstp_handler: signum(%d), sigint_count(%d)\n",
               signum, sigint_count);

        if (--sigint_count <= 0) {
                printf("sigtstp_handler: exiting ...\n");
                exit(1);
        }

#if 0   /* For the original System V signal */
        signal(SIGINT, &sigint_handler);
#endif
}

void sigint_handler(int signum)
{
        printf("sigint_handler: signum(%d), sigint_count(%d)\n",
               signum, sigint_count);

        if (--sigint_count <= 0) {
                printf("sigint_handler: exiting ...\n");
                exit(1);
        }

#if 0   /* For the original System V signal */
        signal(SIGINT, &sigint_handler);
#endif
}

int main(void)
{
        signal(SIGINT, &sigint_handler);
        signal(SIGTSTP, &sigtstp_handler);

        for (;;) {
                printf("main: sigint_count(%d), calling pause ...\n",
                       sigint_count);

                pause();

                printf("main: returned from pause. sigint_count(%d)\n",
                       sigint_count);
        }

        return 0;
}
