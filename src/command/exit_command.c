/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:05 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/05 10:13:56 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned long long	ft_atoull(const char *str)
{
	size_t				index;
	unsigned long long	n;

	index = 0;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '+')
		index++;
	n = 0;
	while (ft_isdigit(str[index]))
	{
		n = n * 10 + (str[index] - '0');
		index++;
	}
	return (n);
}

long long ft_atoll(const char *str)
{
	bool		sign;
	size_t		index;
	long long	n;

	index = 0;
	sign = false;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			sign = true;
		index++;
	}
	n = ft_atoull(&str[index]);
	if (sign)	
		return (-n);
	return (n);
}

static bool	digits_num_is_over_llong_max(const char *str)
{
	size_t	index;

	index = 0;
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index] == '0')
		index++;
	return (ft_strlen(&str[index]) > LLONG_MAX_DIGITS);
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

bool	str_is_valid_num(char *str)
{
	size_t	index;

	index = 0;
	if (str[index] == '-' || str[index] == '+')
		index++;
	if (!ft_str_is_numeric(&str[index]))
		return (false);
	return (str_is_within_llong(str));
}

int	exit_minishell(char **argv)
{
	int				nbr;
	int				exit_nbr;
	const size_t	argv_num = ft_count_strs((const char**)argv);

	if (argv_num == 1)
	{
		put_farewell_picture();
		exit(0);
	}
	if (!str_is_valid_num(argv[1]))
	{
		ft_putstr_err("exit\nbash: exit: ");
		ft_putstr_err(argv[1]);
		ft_putstr_err(": numeric argument required\n");
		exit (255);
	}
	if (argv_num > 2)
	{
		ft_putstr("bash: exit: too many arguments\n");
		return (1); // ?
		// $? = 1
	}
	put_farewell_picture();
	nbr = ft_atoll(argv[1]);
	exit_nbr = ((nbr % 256) + 256) % 256;
	exit (exit_nbr);
	return (0);
}