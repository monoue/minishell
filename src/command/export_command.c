/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:09 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/21 20:09:54 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			put_dbl_quotation_str(char *str)
{
	int		i;
	char	dblQuo;

	i = 0;
	dblQuo = '\"';
	while (str[i])
	{
		write(1, &str[i], 1);
		if (str[i] == '=' || str[i + 1] == '\0')
			write(1, &dblQuo, 1);
		i++;
	}
}

void			show_export(t_list *envp)
{
	int		index;
	char	**array;
	char	dblQota;

	if (envp->content == NULL)
		return ;
	array = turn_envp_into_strs(envp);
	ascii_sort(array);
	index = 0;
	dblQota = '\"';
	while (array[index])
	{
		if (ft_strncmp(array[index], "_=", 2) == 0)
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
	const size_t	len = ft_strlen(arg);
	size_t			index;
	const char		*ng_chars = ".~-#*%()/|<+[]{}:;@?^!\'\"";

	if (len == 0 || arg[0] == '=' || ft_strchr(arg, '\\') || ft_isdigit(arg[0]))
		return (false);
	index = 0;
	while (index < len && arg[index] != '=')
	{
		if (ft_strchr(ng_chars, arg[index]))
			return (false);
		index++;
	}
	return (true);
}

void			check_same_key_or_not(char *key, t_list *envp, char **argv,
																	int index)
{
	char	*arg;
	int		count;

	count = ft_strlen(key);
	if (same_key(key, envp))
	{
		while (envp && envp->next)
		{
			if (ft_strncmp((char*)(envp->content), key, count) == 0
				&& ft_strcmp((char*)(envp->content), argv[index]) != 0)
			{
				SAFE_FREE(envp->content);
				// arg = remove_quotes(argv[index]);
				envp->content = ft_strdup(argv[index]);
			}
			envp = envp->next;
		}
	}
	else if (check_valid_arg(argv[index]))
	{
		// arg = remove_quotes(argv[index]);
		add_variable(argv[index], envp);
	}
	// SAFE_FREE(arg);
}

void			export(char **argv, t_list *envp)
{
	size_t	index;
	char	*key;
	char	*arg;

	if (!argv[1])
		show_export(envp);
	index = 1;
	while (argv[index])
	{
		if (!is_valid_arg(argv[index]))
		{
			put_error_invalid_identifier("export", argv[index]);
			index++;
			continue ;
		}
		key = get_key(argv[index]);
		check_same_key_or_not(key, envp, argv, index);
		index++;
		SAFE_FREE(key);
	}
}
