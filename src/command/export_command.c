/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:09 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/11 10:29:48 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	show_export(t_list *envp)
{
	int		index;
	char	**array;
	char	dblQota;

	if (envp->content == NULL)
		return ;
	array = turn_envp_into_strs(envp);
	ascii_sort(array);
	index = 0;
	dblQota = '"';
	while (array[index])
	{
		if (ft_strncmp(array[index], "_=", 2) == 0 )
			index++;
		ft_putstr_fd("declare -x ", 1);
		put_dbl_quotation_str(array[index]);
		ft_putchar_fd('\n', 1);
		index++;
	}
	ft_free_split(array);
}

static bool	is_valid_arg(char *arg)
{
	size_t	index;
	const char	*ng_chars = "~*()/|<>[]{};?!";
	
	if (arg[0] == '=')
		return (false); // 二文字目以降に出てきたら？？
	index = 0;
	while (arg[index])
	{
		if (ft_strchr(ng_chars, arg[index]))
			return (false);
		index++;
	}
	return (true);
}

void	export(char **argv, t_list *envp)
{
	size_t	index;
	int		count;
	char	*key;
	char	*tmp;

	if (!argv[1])
		show_export(envp);//export コマンドに引数がなかったとき、環境変数を、一覧で表示する
	index = 1;
	while (argv[index])
	{
		key = get_key(argv[index]);
		count = ft_strlen(key);
		if (!is_valid_arg(argv[index]))//環境変数は数字じゃない、または”＝”じゃないを確認する関数。
			return (ft_putstr_fd("bash: export: not a valid identifier\n", 1));
		if (same_key(key, envp))
		{
			while (envp && envp->next)
			{
				tmp = envp->content;
				if (ft_strncmp(tmp, key, count) == 0)
				{
					envp->content = ft_strdup(argv[index]);
				}
				envp = envp->next;
			}
		}
		else if (check_valid_arg(argv[index]))//KEY=VALUEを確認してる関数。
			add_variable(argv[index], envp);
		index++;
	}
}
