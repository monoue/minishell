#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

int main(void)
{
        pid_t pid;

        printf("root getpid:         %d\n", getpid());
        printf("root getppid:        %d\n\n", getppid());

        pid = fork();
        if (pid < 0) {
                fprintf(stderr, "Error fork %d\n", errno);
                exit(EXIT_FAILURE);
        }
        else if (pid != 0){
                //親プロセス処理
                printf("parent's child's pid:%d\n", pid);
                printf("parent getpid:       %d\n", getpid());
                printf("parent getppid:      %d\n\n", getppid());
                // kill(pid, SIGKILL); //子プロセスにシグナルを送信する
                waitpid(pid, NULL, 0); //子プロセス終了を待つ
				printf("hoge");
                exit(0);
        }
        // else if (pid == 0) {
        else {
                //子プロセス処理
                printf("child's child's pid: %d\n", pid);
                printf("child getpid:        %d\n", getpid());
                printf("child getppid:       %d\n", getppid());
                // kill(getppid(), SIGKILL); //子プロセスにシグナルを送信する
                exit(0);
        }

        return 0;
}