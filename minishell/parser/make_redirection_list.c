#include "../minishell.h"

// static void			set_words(t_redirection_set *new, char **elements, size_t start_i, size_t end_i)
// {
// 	size_t	words_i;
// 	size_t	index;

// 	index = start_i;
// 	words_i = 0;
// 	while (index < end_i)
// 	{
// 		new->words[words_i] = elements[index];
// 		index++;
// 	}
// }

// t_redirection_set	*make_redirection_list(char **elements, size_t elements_num)
// {
// 	t_redirection_set	*set;
// 	t_redirection_set	*new;
// 	size_t				index;
// 	size_t				start_i;

// 	index = 0;
// 	while (index < elements_num)
// 	{
// 		new = ft_calloc(1, sizeof(t_redirection_set));
// 		if (!new)
// 			exit_fatal();
// 		if (is_redirection_str(elements[index]))
// 			new->type = get_redirection_type(elements[index++]);
// 		start_i = index;
// 		while (index < elements_num && !is_redirection_str(elements[index]))
// 			index++;	
// 		if (start_i == index)
// 			continue ; // もしくはエラー
// 		new->words = ft_calloc(index - start_i + 1, sizeof(char *));
// 		if (!new->words)
// 			return (NULL);
// 		set_words(new, elements, start_i, index);
// 		lstadd_back(&set, new);
// 	}
// 	return (set);
// }

t_redirection_set	*make_redirection_list(char **elements)
{
	t_redirection_set	*set;
	t_redirection_set	*new;
	size_t				index;
	size_t				start_i;

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

// void	exec_split(char **chunk_words)
// {
// 	t_redirection_set	*set;
// 	t_fd				fds;
// 	size_t				strs_num;
// 	char				**elements;
// 	size_t	index;
// 	size_t	redirection_i;

// 	set_fds(&fds);
// 	index = 0;
// 	redirection_i = 0;
// 	while (chunk_words[index])
// 	{
// 		if (is_redirection_str(chunk_words[index]))	
// 		{
// 			redirection_i = index;
// 			set = make_redirection_list(&chunk_words[index]);
// 			break ;
// 		}
// 		index++;
// 	}
// 	while (set)
// 	{
// 		DS(set->filename);
// 		DI(set->type);
// 		set = set->next;
// 	}
// }

// int main()
// {
// 	char *elements[] = {
// 		"ls",
// 		"hoge",
// 		">",
// 		"a",
// 		"<",
// 		"b",
// 		">>",
// 		"c",
// 		NULL
// 	};
// 	// t_redirection_set *set = exec_split(elements);
// 	exec_split(elements);
// 	// size_t	index = 0;
// 	// while ([index])
// 	// {
		
// 	// 	index++;
// 	// }
// }