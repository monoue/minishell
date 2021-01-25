#include "minishell.h"

void    env(char **environ)
{
    int index;

    index = 0;
    while(environ[index])
    {
        ft_putstr_fd(environ[index], 1);
        ft_putchar_fd('\n', 1);
        index++;
    }
}