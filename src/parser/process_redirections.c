#include "minishell.h"

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

static t_redirection_set	*make_redirection_list(char **elements,
																t_list *envp)
{
	t_redirection_set	*set;
	t_redirection_set	*new;
	size_t				index;
	char				*filename;

	index = 0;
	set = NULL;
	while (elements[index])
	{
		new = ft_calloc(1, sizeof(t_redirection_set));
		if (!new)
			exit_err_msg(MALLOC_ERR);
		new->type = get_redirection_type(elements[index]);
		filename = elements[index + 1];
		if (dollar_or_not(filename, '$')
			&& replace_dollar_value(filename, envp, 0)[0] == '\0')
			exit_bash_err_msg(filename, AMBIGUOUS_ERR, EXIT_FAILURE);
		new->filename = ft_strdup(filename);
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

	if (set->filename[0] == '\0')
		exit_bash_err_msg("", strerror(ENOENT), EXIT_FAILURE);
	file_fd = open(set->filename, get_open_flags(type), OPEN_MODE);
	if (file_fd == ERROR)
		exit_err_msg(strerror(errno));
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

static void					set_redirections(char **chunk_words, t_fd *fds,
																t_list *envp)
{
	t_redirection_set	*set;

	set = make_redirection_list(chunk_words, envp);
	while (set)
	{
		set_redirection(set, fds);
		set = set->next;
	}
}

size_t						process_redirections(char **chunk_words, t_fd *fds,
																t_list *envp)
{
	size_t	index;

	index = 0;
	while (chunk_words[index])
	{
		if (is_redirection_str(chunk_words[index]))
		{
			set_redirections(&chunk_words[index], fds, envp);
			break ;
		}
		index++;
	}
	return (index);
}
