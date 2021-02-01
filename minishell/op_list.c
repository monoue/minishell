#include "minishell.h"

// t_chunk	*lstlast(t_chunk *chunk)
// {
// 	if (!chunk)
// 		return (NULL);
// 	while (chunk->next)
// 		chunk = chunk->next;
// 	return (chunk);
// }

// void	lstadd_back(t_chunk **chunks, t_chunk *new)
// {
// 	t_chunk	*tmp;

// 	if (!chunks || !new)
// 		return ;
// 	if (!(*chunks))
// 	{
// 		*chunks = new;
// 		return ;
// 	}
// 	tmp = lstlast(*chunks);
// 	tmp->next = new;
// 	new->prev = tmp;
// }

t_redirection_set	*lstlast(t_redirection_set *set)
{
	if (!set)
		return (NULL);
	while (set->next)
		set = set->next;
	return (set);
}

void	lstadd_back(t_redirection_set **sets, t_redirection_set *new)
{
	t_redirection_set	*set;

	if (!sets || !new)
		return ;
	if (!(*sets))
	{
		*sets = new;
		return ;
	}
	set = lstlast(*sets);
	set->next = new;
	new->prev = set;
}
