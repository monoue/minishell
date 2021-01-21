#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
        int file_fd;

        if (argc != 2) {
                fprintf(stderr, "Usage: %s file_name\n", argv[0]);
                exit(1);
        }

        file_fd = open(argv[1], O_RDONLY); // ファイルに fd 割り当て
        if (file_fd < 0) {
			perror("open");
			exit(1);
        }

        close(0); // 標準入力を閉じる
        if (dup2(file_fd, 0) < 0) // ファイルの fd を標準入力に付け替え
		{
			perror("dup2");
			close(file_fd);
			exit(1);
        }
        close(file_fd); // ファイルの fd を閉じる

        execlp("wc", "wc", NULL); // wc コマンドは、fd による入力を受け付けるコマンドなので、このようなことができる。

        return 1;
}
