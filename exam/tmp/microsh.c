#include <stdio.h> //delete
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> //for linux
#include <sys/wait.h> //for linux

#define ERROR		-1

#define STDIN		0
#define STDERR		2

#define TYPE_END	3
#define TYPE_PIPE	4
#define TYPE_BREAK	5

typedef struct s_base
{
    char **argv;
    int size;
	int type;
	int pipefds[2];
	struct s_base *prev;
    struct s_base *next;
} t_chunk;

/*
**====================================
**============Part utils==============
**====================================
*/

int ft_strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char *ft_strdup(char *str)
{
	int size = ft_strlen(str);
	char *new;

	if (!str)
		return (NULL);
	if (!(new = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	new[size] = '\0';
	while (--size >= 0)
		new[size] = str[size];
	return (new);
}

/*
**====================================
**============Part error==============
**====================================
*/

void exit_fatal(void)
{
	write(STDERR, "error: fatal\n", ft_strlen("error: fatal\n"));
	exit(EXIT_FAILURE);
}

void exit_execve(char *str)
{
	write(STDERR, "error: cannot execute ", ft_strlen("error: cannot execute "));
	write(STDERR, str, ft_strlen(str));
	write(STDERR, "\n", 1);
	exit(EXIT_FAILURE);
}

int exit_cd_1()
{
	write(STDERR, "error: cd: bad arguments\n", ft_strlen("error: cd: bad arguments\n"));
	return (EXIT_FAILURE);
}

int exit_cd_2(char *str)
{
	write(STDERR, "error: cd: cannot change directory to ", ft_strlen("error: cd: cannot change directory to "));
	write(STDERR, str, ft_strlen(str));
	write(STDERR, "\n", 1);
	return (EXIT_FAILURE);
}

/*
**====================================
**============Part parsing============
**====================================
*/

void ft_lstadd_back(t_chunk **lst, t_chunk *new)
{
    t_chunk *temp;

	if (!(*lst))
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}

int count_args(char **argv)
{
    int i = 0;
    while (argv[i] && strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0)
        i++;
    return (i);
}

int get_type(char *av)
{
    if (!av)
        return (TYPE_END);
    if (strcmp(av, "|") == 0)
        return (TYPE_PIPE);
    if (strcmp(av, ";") == 0)
        return (TYPE_BREAK);
    return (0);
}

int add_parsed_info_back(t_chunk **lst, char **av)
{
    int size = count_args(av);
    t_chunk *new;

    if (!(new = (t_chunk *)malloc(sizeof(t_chunk))))
        exit_fatal();
    if (!(new->argv = (char **)malloc(sizeof(char *) * (size + 1))))
        exit_fatal();
    new->size = size;
	new->next = NULL;
	new->prev = NULL;
    new->argv[size] = NULL;
    while (--size >= 0)
        new->argv[size] = ft_strdup(av[size]);
    new->type = get_type(av[new->size]);
    ft_lstadd_back(lst, new);
    return (new->size);
}

/*
**====================================
**============Part execve=============
**====================================
*/

void exec_cmd(t_chunk *temp, char **env)
{
	pid_t pid;
	int status;
	int pipe_open;

	pipe_open = 0;
	if (temp->type == TYPE_PIPE || (temp->prev && temp->prev->type == TYPE_PIPE))
	{
		pipe_open = 1;
		if (pipe(temp->pipefds))
			exit_fatal();
	}
	pid = fork();
	if (pid == ERROR)
		exit_fatal();
	else if (pid == 0) //child
	{
		if (temp->type == TYPE_PIPE && dup2(temp->pipefds[1], STDOUT_FILENO) < 0)
			exit_fatal();
		if (temp->prev && temp->prev->type == TYPE_PIPE && dup2(temp->prev->pipefds[0], STDIN) < 0)
			exit_fatal();
		if ((execve(temp->argv[0], temp->argv, env)) < 0)
			exit_execve(temp->argv[0]);
		exit(EXIT_SUCCESS);
	}
	else //parent
	{
		waitpid(pid, &status, 0);
		if (pipe_open)
		{
			close(temp->pipefds[1]);
			if (!temp->next || temp->type == TYPE_BREAK)
				close(temp->pipefds[0]);
		}
		if (temp->prev && temp->prev->type == TYPE_PIPE)
			close(temp->prev->pipefds[0]);
	}
}

void exec_cmds(t_chunk *ptr, char **env)
{
	t_chunk *tmp;

	tmp = ptr;
	while (tmp)
	{
		if (strcmp("cd", tmp->argv[0]) == 0)
		{
			if (tmp->size < 2)
				exit_cd_1();
			else if (chdir(tmp->argv[1]))
				exit_cd_2(tmp->argv[1]);
		}
		else
			exec_cmd(tmp, env);
		tmp = tmp->next;
	}
}

/*
**====================================
**============Part main===============
**====================================
*/

void clear_leaks(t_chunk *ptr)
{
	t_chunk *temp;
	int i;

	while (ptr)
	{
		temp = ptr->next;
		i = 0;
		while (i < ptr->size)
			free(ptr->argv[i++]);
		free(ptr->argv);
		free(ptr);
		ptr = temp;
	}
	ptr = NULL;
}

int main(int ac, char **av, char **env)
{
	t_chunk *lst = NULL;

	int i;

	i = 1;
	if (ac > 1)
	{
		while (av[i])
    	{
            if (strcmp(av[i], ";") == 0)
            {
                i++;
                continue ;
            }
    	    i += add_parsed_info_back(&lst, &av[i]);
    	    if (!av[i])
    	        break;
    	    else
    	        i++;
    	}
	/*while (ptr)
	{

		printf("=================\n");
		for (i = 0; i < ptr->size; i++)
			printf("%s\n", ptr->argv[i]);
		printf("TYPE: %d\n", ptr->type);
		printf("SIZE: %d\n", ptr->size);
		printf("=================\n");
		ptr = ptr->next;
	}
	(void)**env;
	printf("END\n");*/
		if (lst)
			exec_cmds(lst, env);
		clear_leaks(lst);
	}
	return (0);
}
