/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/02/26 11:53:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_last_exit_status = 0;

//#define BUFFER_SIZE 2000

int		g_sigint_flag;

int		g_tmp = 0;

int		ft_getline_2(int *cmd_status, char **stock, int *flag)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;
	char	*tmp;

	ret = read(0, buf, BUFFER_SIZE);
	if (g_tmp == 1)
	{
		*cmd_status = 256;
		free(*stock);
		*stock = ft_strdup("");
		g_tmp = 0;
	}
	if (buf[ret - 1] == '\n')
	{
		*flag = 0;
		buf[ret - 1] = 0;
	}
	buf[ret] = 0;
	tmp = *stock;
	*stock = ft_strjoin(*stock, buf);
	free(tmp);
	return (ret);
}

char	*ft_getline(int *cmd_status)
{
	char	*stock;
	int		flag;
	int		ret;

	g_tmp = 0;
	flag = 1;
	stock = ft_strdup("");
	while (flag && (stock != NULL))
	{
		ret = ft_getline_2(cmd_status, &stock, &flag);
		write(2, "  \b\b", 4);
		if (ret == 0 && *stock)
			;
		else if (ret == 0)
		{
			ft_putendl_err("exit");
			exit(*cmd_status / 256);
		}
	}
	return (stock);
}


void	handle_gl(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\b\b  ", 4);
		write(2, "\n\033[31m$❯\033[0m ", ft_strlen("\n\033[31m$❯\033[0m "));
		g_tmp = 1;
		g_last_exit_status = 1;
	}
	if (sig == SIGQUIT)
	{
		write(2, "\b\b  \b\b", 6);
	}
}

static void	main_loop(t_list *envp)
{
	int			ret = 0;
	char		*line;

	int			cmd_status = 0;

	ft_putstr_err(PROMPT);
	set_signal_handlers();
//	ret = get_next_line(STDIN_FILENO, &line);
	signal(SIGINT, handle_gl);
	signal(SIGQUIT, handle_gl);
	line = ft_getline(&cmd_status);
	set_signal_handlers();

	if (ret == ERROR)
		exit_err_msg(MALLOC_ERR);
	if (ret == FILE_END && line)
		;
	else if (ret == FILE_END)
	{
		put_farewell_greeting();
		exit(EXIT_SUCCESS);
	}
	if (str_is_of_tabs_or_spaces(line) || put_message_if_syntax_error(line))
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
