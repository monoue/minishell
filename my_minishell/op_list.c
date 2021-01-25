#include "minishell.h"

t_chunk	*lstlast(t_chunk *chunk)
{
	if (!chunk)
		return (NULL);
	while (chunk->next)
		chunk = chunk->next;
	return (chunk);
}

void	lstadd_back(t_chunk **chunks, t_chunk *new)
{
	t_chunk	*tmp;

	if (!chunks || !new)
		return ;
	if (!(*chunks))
	{
		*chunks = new;
		return ;
	}
	tmp = lstlast(*chunks);
	tmp->next = new;
	new->prev = tmp;
}
