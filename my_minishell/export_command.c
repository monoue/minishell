#include "minishell.h"

void	ascii_sort(char **args)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		j = i + 1;
		while (args[j])
		{
			if (ft_strcmp(args[i], args[j]) > 0)
			{
				tmp = args[i];
				args[i] = args[j];
				args[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char    **copy_env(t_list *environ)
{
    char    **ret;
    int     i;

    i = 0;
    if (!(ret = malloc(sizeof(char *) * (ft_lstsize(environ) + 1))))
        return (NULL);
    i = 0;
    while (environ)
    {
        ret[i] = ft_strdup(environ->content);
        i++;
        environ = environ->next;
	}
	ret[i] = NULL;
	return (ret);
}

void    put_dbl_quotation_str(char *str)
{
    int     i;
    char    dblQuo;

    i = 0;
    dblQuo = '"';
    while(str[i])
    {
        write(1, &str[i], 1);
        if (str[i] == '=' || str[i + 1] == '\0')
            write(1, &dblQuo, 1);
        i++;
    }
}

void    show_export(t_chunk *chunk, t_list *environ)
{
    int     index;
    int     i;
    char    **array; 
    char    dblQota;

    array = copy_env(environ);
    ascii_sort(array);
    index = 0;
    dblQota = '"';
    
    while (array[index])
    {
        ft_putstr_fd("declare -x ", 1);
        put_dbl_quotation_str(array[index]);
        ft_putchar_fd('\n', 1);
        index++;
    }
}

// int     check_valid_arg(t_chunk *chunk)
// {
    
// }

void    export(t_chunk *chunk, char **environ)
{
    int     i;
    t_list  *envp;
    t_list  *tmp;

    //環境変数をリスト構造に初期化する。
    envp = ft_lstnew(*environ);
    environ++;
    while(*environ)
    {
        tmp = ft_lstnew(*environ);
        ft_lstadd_back(&envp, tmp);
        environ++;
    }
    i = 0;
    if (!chunk->argv[1])
        show_export(chunk, envp); //export コマンドに引数がなかったとき、環境変数を、一覧で表示する
    // while (chunk->argv[i])
    // {
    //     if (chek_valid_arg(chunk))
    //         add_var(chunk, envp);
    // }
}