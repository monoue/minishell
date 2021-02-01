#include "../minishell.h"

void	exit_fatal(void)
{
	ft_putstr_err(FATAL_ERR_MSG);
	exit(EXIT_FAILURE);
}

void	exit_err_msg(char *err_msg)
{
	ft_putstr_err(err_msg);
	exit(EXIT_FAILURE);
}