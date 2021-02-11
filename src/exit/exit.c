#include "minishell.h"

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

void	exit_bash_err_msg(char *error_factor, char *error_reason)
{
	ft_putstr_err("bash: ");
	ft_putstr_err(error_factor);
	ft_putstr_err(": ");
	ft_putendl_err(error_reason);
	exit(EXIT_SUCCESS);
}
