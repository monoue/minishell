#include "minishell.h"



int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	int			fd;

	(void)argc;
	(void)argv;
	ft_bzero(&minishell, sizeof(t_minishell));
	minishell.current_dir = getcwd(NULL, 0);
	env_init(&minishell, env);
}