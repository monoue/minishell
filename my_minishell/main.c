/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/01/22 12:40:23 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MALLOC_ERR "memory allocation error\n"

void	exit_err_msg(char *err_msg)
{
	ft_putstr_err(err_msg);
	exit(EXIT_FAILURE);
}

int	cd(char **args);
int	help(char **args);
int	lsh_exit(char **args);

char	*builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int	(*builtin_func[])(char **) = {
	&cd,
	&help,
	&lsh_exit
};

int	num_builtins()
{
	return (sizeof(builtin_str) / sizeof(char *));
}

int	cd(char **args)
{
	if (args[1] == NULL)
	{
		if (chdir("/") == ERROR)
			perror("");
	}
	else
	{
		if (chdir(args[1]) == ERROR)
			perror("");
	}
	return 1;
}

int	help(char **args)
{
	int	i;

	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in: \n");
	i = 0;	
	while (i < num_builtins())
	{
		printf(" %s\n", builtin_str[i]);
		i++;
	}
	return (1);
}

int	lsh_exit(char **args)
{
	return (0);
}

// int		launch(char **args)
// {
// 	extern char	**environ;
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid == ERROR)
// 		perror("");
// 	else if (pid == 0) // 子プロセス
// 	{
// 		if (execve(args[0], args, environ) == ERROR)
// 			exit_err_msg("execvp failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		status = false;
// 		while (!WIFEXITED(status) && !WIFSIGNALED(status))
// 			waitpid(pid, &status, WUNTRACED); // 子プロセスが停止した場合にも復帰する。
// 	}
// 	return (1);
// }

// int		execute(char **args)
// {
// 	int	i;

// 	if (!args[0])
// 		return (1);
// 	i = 0;
// 	while (i < num_builtins())
// 	{
// 		if (ft_strequal(args[0], builtin_str[i]))
// 			return ((*builtin_func[i])(args));
// 		i++;
// 	}
// 	return (launch(args));
// }

void	loop(void)
{
	t_chunk	*chunk;
	t_chunk	*new;
	// ここまで追加

	char	*line;
	char	**args;
	int		status;

	status = true;
	while (status)
	{
		ft_putstr("❯ ");
		if (get_next_line(STDIN_FILENO, &line) == ERROR)
			exit_err_msg(MALLOC_ERR);
		args = ft_split(line, ' ');

		// status = execute(args); 以下、この一行を、exam バージョンに変更中
		// ここから
		
		

		// ここまで
		SAFE_FREE(line);
		ft_free_split(args);
	}
}

int main(int argc, char **argv, char **env)
{
	ft_putstr_err("❤️\n");
	loop();
	return (EXIT_SUCCESS);
}
