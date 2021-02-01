/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:09 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/01 06:33:48 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_env(t_list *environ)
{
	char	**ret;
	int		i;

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

void	put_dbl_quotation_str(char *str)
{
	int		i;
	char	dblQuo;

	i = 0;
	dblQuo = '"';
	while (str[i])
	{
		write(1, &str[i], 1);
		if (str[i] == '=' || str[i + 1] == '\0')
			write(1, &dblQuo, 1);
		i++;
	}
}

void	show_export(t_chunk *chunk, t_list *environ)
{
	int		index;
	int		i;
	char	**array;
	char	dblQota;

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

void	add_variable(char *argv, t_list *envp)
{
	//t_list *new;
	//char *tmp;

	//tmp  = ft_strdup(argv);
	//new = ft_lstnew(tmp);
	//ft_lstadd_back(&envp, new);
	t_list	*new;
	t_list	*tmp;

	new = malloc(sizeof(t_list));
	new->content = ft_strdup(argv);
	while (envp && envp->next && envp->next->next)
		envp = envp->next;
	tmp = envp->next;
	envp->next = new;
	new->next = tmp;
}

void	export(t_chunk *chunk, t_list *envp)
{
	int		i;
	int		count;
	char	*key;
	char	*tmp;

	i = 0;
	//EXPORTはまだ動いたない、２月２７日に直すよ
	//key = //ici je trouve une fonction qui prend jusqua "=" 
	if (!chunk->argv[1])
		show_export(chunk, envp);//export コマンドに引数がなかったとき、環境変数を、一覧で表示する
	while (chunk->argv[i])
	{
		count = ft_strlen(key);
		if (!arg_is_str(chunk->argv[i]))//環境変数は数字じゃない、または”＝”じゃないを確認する関数。
			return (ft_putstr_fd("bash: export: not a valid identifier\n", 1));
		if (is_key_duplicated(key, envp))
		{
			while (envp && envp->next)
			{
				tmp = envp->content;
				if (ft_strncmp(tmp, chunk->argv[i], count) == 0)
				{
					delete_variable(envp->content);
					add_variable(chunk->argv[i], envp);
				}
				envp = envp->next;
			}
		}
		else if (check_valid_arg(chunk->argv[i]))//KEY=VALUEを確認してる関数。
				add_variable(chunk->argv[i], envp);
		i++;
	}
}
