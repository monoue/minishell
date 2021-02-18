/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:09 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/18 16:33:04 by monoue           ###   ########.fr       */
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


// static void	put_error_message(const char *arg)
// {
// 	ft_putstr("bash: export: `");
// 	ft_putstr(arg);
// 	ft_putendl("': not a valid identifier");
// }

void	export(char **argv, t_list *envp)
{
	size_t	index;
	char	*key;

	if (!argv[1])
		show_export(envp);//export コマンドに引数がなかったとき、環境変数を、一覧で表示する
	index = 1;
	while (argv[index])
	{
		if (!is_valid_arg(argv[index]))
		{
			put_error_message(argv[index]);
			index++;
			continue ;
		}
		key = get_key(argv[index]);
		if (same_key(key, envp))
		{
			while (envp && envp->next)
			{
				if (ft_strnequal((char*)(envp->content), key, ft_strlen(key)))
					envp->content = ft_strdup(remove_quotes(argv[index]));
				envp = envp->next;
			}
		}
		add_variable(remove_quotes(argv[index]), envp);
		SAFE_FREE(key);
		index++;
	}
}
