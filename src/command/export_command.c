/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:09 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/02 14:12:08 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			put_dbl_quotation_str(char *str)
{
	int		i;
	int		a;
	char	dblq;

	i = 0;
	a = 0;
	dblq = '\"';
	while (str[i])
	{
		write(1, &str[i], 1);
		if (str[i] == '=' || str[i + 1] == '\0')
		{
			if (a == 0 && str[i + 1] == '\0')
				write(1, &dblq, 1);
			a = 1;
			write(1, &dblq, 1);
		}
		i++;
	}
}

void			show_export(t_list *envp)
{
	int		index;
	char	**array;
	char	dblq;

	if (envp->content == NULL)
		return ;
	array = turn_envp_into_strs(envp);
	ascii_sort(array);
	index = 0;
	dblq = ('\"');
	while (array[index])
	{
		if (ft_strncmp(array[index], "_=", 2) == 0)
			index++;
		if (array[index] == NULL)
			return ;
		ft_putstr_fd("declare -x ", 1);
		put_dbl_quotation_str(array[index]);
		ft_putchar_fd('\n', 1);
		index++;
	}
	ft_free_split(array);
}

static bool		is_valid_arg(char *arg)
{
	const size_t	len = ft_strlen(arg);
	size_t			index;

	if (arg == NULL)
		return (false);
	if (len == 0 || arg[0] == '=' || ft_strchr(arg, '\\') || ft_isdigit(arg[0]))
		return (false);
	index = 0;
	while (index < len && arg[index] != '=')
	{
		if (!ft_isalnum(arg[index]) && arg[index] != '_' 
		&& arg[index] != '\"' && arg[index] != '\'')
			return (false);
		index++;
	}
	return (true);
}

void			check_same_key_or_not(char *key, t_list *envp, char **argv,
																	int index)
{
	int		count;
	char	*arg;

	arg = ft_strdup(argv[index]);
	count = ft_strlen(key);
	if (same_key(key, envp))
	{
		while (envp && envp->next)
		{
			if (ft_strncmp((char*)(envp->content), key, count) == 0
				&& ft_strcmp((char*)(envp->content), argv[index]) != 0)
			{
				SAFE_FREE(envp->content);
				envp->content = ft_strdup(argv[index]);
			}
			envp = envp->next;
		}
	}
	else if (check_valid_arg(arg))
		add_variable(arg, envp);
	SAFE_FREE(arg);
}

void			export(char **argv, t_list *envp)
{
	size_t	index;
	char	*key;
	char	**arg;

	arg = set_command_argv(argv, envp);
	if (arg[1] == NULL)
		show_export(envp);
	index = 1;
	while (arg[index])
	{
		key = get_key(arg[index]);
		if (!is_valid_arg(key))
		{
			put_error_invalid_identifier("export", arg[index]);
			index++;
			SAFE_FREE(key);
			continue ;
		}
		check_same_key_or_not(key, envp, arg, index);
		index++;
		SAFE_FREE(key);
	}
	ft_free_split(arg);
}
