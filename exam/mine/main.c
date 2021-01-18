#include "microshell.h"

// void	list_rewind(t_list **list)
// {
// 	while (*list && (*list)->previous)
// 		*list = (*list)->previous;
// }

void	ft_putstr_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
}

// int		exit_fatal(void)
// {
// 	ft_putstr_error("error: fatal\n");
// 	exit(EXIT_FAILURE);
// 	return (EXIT_FAILURE); // 要らないのでは…？
// }


void	ft_lstadd_back(t_base **lst, t_base *new)
{
	t_base	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->previous = tmp;
	}
}

int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL && strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0)
		i++;
	return (i);
}


int	get_last_arg_type(char *arg)
{
	if (arg == NULL)
		return (TYPE_END);
	if (strcmp(arg, "|") == 0)
		return (TYPE_PIPE);
	if (strcmp(arg, ";") == 0)
		return (TYPE_BREAK);
	return (0);
}

int	add_parsed_info_back(t_base **lst, char **argv)
{
	int		size;
	t_base	*new;

	new = malloc(sizeof(t_base));
	if (new == NULL)
		exit_fatal();
	size = count_args(argv);
	new->argv = malloc(sizeof(char *) * (size + 1));
	if (new->argv == NULL)
		exit_fatal();
	new->size = size;
	new->next = NULL;
	new->previous = NULL;
	new->argv[size] = NULL;
	int	index;

	index = 0;
	while (index < size)
	{
		new->argv[index] = ft_strdup(argv[index]);
		if (new->argv[index] == NULL)
			return (NULL);
		index++;
	}
	new->type = get_last_arg_type(argv[new->size]); // 区切れの最後の要素
	ft_lstadd_back(lst, new); // 本家とは、「空なら作る」点が異なる。
	return (new->size);
}

int main(int argc, char *argv[], char **env)
{
	t_base	*lst = NULL;
	int		i;

	if (argc <= 1)
		return (EXIT_SUCCESS);
	i = 1;
	while (argv[i])
	{
		if (strcmp(argv[i], ";") == 0)
		{
			i++;
			continue;
		}
		i += add_parsed_info_back(&lst, &argv[i]); // どうやら、argv を、区切られた塊ごとの文字列の配列に分けているのでは…？
		if (argv[i] == NULL)
			break;
		i++;
	}
	if (lst)
		exec_cmds(lst, env);
	clear_leaks(lst);
}