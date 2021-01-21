#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int pipe_fd[2];

void do_child(void)
{
        char *p = "Hello, dad or mam!\n";

        printf("This is child.\n");

        close(pipe_fd[0]); // 読み込み側を削除。

        close(1);
        if (dup2(pipe_fd[1], 1) < 0) { // 1 が書き込み側になった。
                perror("dup2 (child)");
                exit(1);
        }
        close(pipe_fd[1]); // こっちは削除してやる。

        while (*p) {
                putchar(*p++); // 1 に出している。それが書き込まれて、0 の標準入力につなげられている。
        }
}

void do_parent(void)
{
        char c;
        int status;

        printf("This is parent.\n");

        close(pipe_fd[1]); // 入力側を閉じている

        close(0); // こうしてやらないと、0 を割り当ててやれない
        if (dup2(pipe_fd[0], 0) < 0) { // 0 は、読み込み側になった。
                perror("dup2 (parent)");
                exit(1);
        }
        close(pipe_fd[0]); // こっちは削除してやる。

        while ((c = getchar()) != EOF) { // ここで拾っている。
                putchar(c);
        }

        if (wait(&status) < 0) {
                perror("wait");
                exit(1);
        }
}

int main(void)
{
        int child;

        if (pipe(pipe_fd) < 0) {
                perror("pipe");
                exit(1);
        }

        if ((child = fork()) < 0) {
                perror("fork");
                exit(1);
        }

        if (child) {
                do_parent();
        } else {
                do_child();
        }

        return 0;
}
