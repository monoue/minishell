
#include "minishell.h"

void	set_fds(t_fd *fds)
{
	fds->input = STDIN_FILENO;
	fds->output = STDOUT_FILENO;
}
