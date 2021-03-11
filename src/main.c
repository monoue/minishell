/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/03/11 10:05:07 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_last_exit_status = 0;
bool	g_tmp = false;

static int	ft_getline_2(int *cmd_status, char **stock, int *flag)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;
	char	*tmp;

	ret = read(0, buf, BUFFER_SIZE);
	if (g_tmp)
	{
		*cmd_status = 256;
		free(*stock);
		*stock = ft_strdup("");
		g_tmp = false;
	}
	if (ret > 0 && buf[ret - 1] == '\n')
	{
		*flag = false;
		buf[ret - 1] = 0;
	}
	buf[ret] = 0;
	tmp = *stock;
	*stock = ft_strjoin(*stock, buf);
	free(tmp);
	return (ret);
}

static char	*ft_getline(int *cmd_status)
{
	char	*stock;
	int		flag;
	int		ret;

	g_tmp = false;
	flag = true;
	stock = ft_strdup("");
	while (flag && (stock != NULL))
	{
		ret = ft_getline_2(cmd_status, &stock, &flag);
		ft_putstr_err("  \b\b");
		if (ret == 0 && !(*stock))
		{
			ft_putendl_err("exit");
			put_farewell_greeting();
			exit(*cmd_status / 256);
		}
	}
	return (stock);
}

static void	handle_gl(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_err("\b\b  ");
		ft_putstr_err("\n\033[31m$❯\033[0m ");
		g_tmp = true;
		g_last_exit_status = 1;
	}
	if (sig == SIGQUIT)
		ft_putstr_err("\b\b  \b\b");
}

static void	main_loop(t_list *envp)
{
	char		*line;
	int			cmd_status;

	cmd_status = 0;
	ft_putstr_err(PROMPT);
	set_signal_handlers();
	signal(SIGINT, handle_gl);
	signal(SIGQUIT, handle_gl);
	line = ft_getline(&cmd_status);
	set_signal_handlers();
	if (str_is_of_tabs_or_spaces(line) || put_message_if_syntax_error(line)
		|| (has_dollar_variable(line) && !(dollar(line, envp))))
	{
		SAFE_FREE(line);
		return ;
	}
	process_command_line(line, envp);
}

int			main(void)
{
	t_list		*envp;

	put_welcome_greeting();
	envp = get_env_list();
	while (42)
		main_loop(envp);
}
