/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:05 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/03 08:38:00 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_error_numeric(char *argv)
{
	ft_putstr_err("bash: exit: ");
	ft_putstr_err(argv);
	ft_putstr_err(": numeric argument required\n");
	exit(255);
}

static bool	str_is_within_llong(const char *str)
{
	bool				sign;
	unsigned long long	n;
	size_t				index;

	index = 0;
	if (digits_num_is_over_llong_max(str))
		return (false);
	sign = false;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = true;
		index++;
	}
	n = ft_atoull(&str[index]);
	if (n == 0)
		return (true);
	if (sign)
		n--;
	return (n <= LLONG_MAX);
}

static bool	str_is_valid_num(char *str)
{
	size_t	index;

	index = 0;
	while (str[index] == ' ')
		index++;
	if ((str[index] == '-' && str[index + 1] != '\0')
		|| (str[index] == '+' && str[index + 1] != '\0'))
		index++;
	if (!ft_str_is_numeric(&str[index]))
		return (false);
	return (str_is_within_llong(str));
}

static void	exit_minishell2(int argv_num, char **arg, bool pipe_child)
{
	int	nbr;
	int	exit_nbr;

	if (argv_num > 2)
	{
		put_bash_err_msg("exit", "too many arguments");
		ft_free_split(arg);
		g_last_exit_status = EXIT_FAILURE;
		return ;
	}
	if (!pipe_child)
		put_farewell_greeting();
	nbr = ft_atoll(arg[1]);
	exit_nbr = ((nbr % 256) + 256) % 256;
	ft_free_split(arg);
	exit(exit_nbr);
}

void		exit_minishell(char **argv, t_list *envp, bool pipe_child)
{
	char	**arg;
	size_t	argv_num;

	arg = set_command_argv(argv, envp);
	argv_num = ft_count_strs((const char **)arg);
	if (!pipe_child)
		ft_putendl_err("exit");
	if (argv_num == 1)
	{
		if (!pipe_child)
			put_farewell_greeting();
		ft_free_split(arg);
		exit(g_last_exit_status);
	}
	if (!str_is_valid_num(arg[1]))
	{
		put_error_numeric(arg[1]);
		if (!pipe_child)
			put_farewell_greeting();
		ft_free_split(arg);
		exit(255);
	}
	exit_minishell2(argv_num, arg, pipe_child);
}
