#include "../minishell.h"

static int					get_open_flags(t_type type)
{
	if (type == TYPE_INPUT)
		return (O_RDONLY);
	if (type == TYPE_OUTPUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == TYPE_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (ERROR);
}

static t_redirection_set	*make_redirection_list(char **elements)
{
	t_redirection_set	*set;
	t_redirection_set	*new;
	size_t				index;

	index = 0;
	set = NULL;
	while (elements[index])
	{
		new = ft_calloc(1, sizeof(t_redirection_set));
		if (!new)
			exit_fatal();
		new->type = get_redirection_type(elements[index]);
		new->filename = ft_strdup(elements[index + 1]);
		lstadd_back(&set, new);
		index += 2;
	}
	return (set);
}

static void					set_redirection(t_redirection_set *set, t_fd *fds)
{
	int				file_fd;
	int				*p_fd;
	int				std_fd;
	const t_type	type = set->type;

	file_fd = open(set->filename, get_open_flags(type), OPEN_MODE);
	if (file_fd == ERROR)
		exit_fatal();
	if (type == TYPE_INPUT)
	{
		p_fd = &(fds->input);
		std_fd = dup(*p_fd);
		close(*p_fd);
		dup2(file_fd, STDIN_FILENO);
	}
	else
	{
		p_fd = &(fds->output);
		std_fd = dup(*p_fd);
		close(*p_fd);
		dup2(file_fd, STDOUT_FILENO);
	}
	close(file_fd);
	*p_fd = std_fd;
}

void					set_redirections(char **chunk_words, t_fd *fds)
{
	t_redirection_set	*redirection_set;

	redirection_set = make_redirection_list(chunk_words);
	while (redirection_set)	
	{
		set_redirection(redirection_set, fds);
		redirection_set = redirection_set->next;
	}
}

size_t	process_redirections(char **chunk_words, t_fd *fds)
{
	size_t	index;

	index = 0;
	while (chunk_words[index])
	{
		if (is_redirection_str(chunk_words[index]))	
		{
			set_redirections(&chunk_words[index], fds);
			break ;
		}
		index++;
	}
	return (index);
}
