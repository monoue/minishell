/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_handlers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/02/12 10:30:31 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** removes letters given by sending signals
*/

static void	remove_display_trash(void)
{
	ft_putstr_err(TRASH_REMOVER);
}

/*
** handles signal given by "ctrl + c"
*/

static void	handle_interruption_signal(int signo)
{
	(void)signo;
	g_last_exit_status = 1;
	if (g_pid != 0)
	{
		kill(g_pid, SIGINT);
		ft_putchar_err('\n');
		g_pid = 0;
	}
	else
	{
		remove_display_trash();
		ft_putchar_err('\n');
		ft_putstr_err(PROMPT);
	}
}

/*
** handles signal given by "ctrl + \"
*/

static void	handle_quit_signal(int signo)
{
	(void)signo;
	if (g_pid != 0)
	{
		kill(g_pid, SIGQUIT);
		ft_putendl_err(QUIT_MSG);
	}
	else
		remove_display_trash();
}

void		set_signal_handlers(void)
{
	signal(SIGINT, handle_interruption_signal);
	signal(SIGQUIT, handle_quit_signal);
}
