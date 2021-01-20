#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char	*builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int	(*builtin_func[])(char **) = {
	&lsh_cd,
	&lsh_help,
	&lsh_exit
}

char	*lsh_read_line(void)
{
#ifdef LSH_USE_STD_GETLINE
	char	*line = NULL;
	ssize_t bufsize = 0;
	if (getline(&line, &ufsize, stdin) == -1)
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);
		else
		{
			perror("lsh: getline\n");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
#else
#define LSH_RL_BUFSIZE	1024
	int		bufsize = LSH_RL_BUFSIZE;
	int		position = 0;
	char	*buffer;
	int		c;

	buffer = malloc(sizeof(char) * bufsize);
	if (!buffer)
	{
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		c = getchar();
		if (c == EOF)
			exit(EXIT_SUCCESS);
		if (c == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}
		buffer[position] = c;
		position++;
		if (position >= bufsize)
		{
			bufsize += LSH_RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
#endif
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char	**lsh_split_line(char *line)
{
	int		bufsize = LSH_TOK_BUFSIZE;
	int		position = 0;
	char	**tokens = malloc(sizeof(char *) * bufsize);
	char	*token;
	char	**tokens_backup;

	if (!tokens)
	{
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, LSH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		if (position >= bufsize)
		{
			bufsize += LSH_TOK_BUFSIZE;
			tokens_backup = tokens;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				free(tokens_backup);
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, LSH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

int	lsh_execute(char **args)
{
	int	i;

	if (args[0] == NULL)
		return 1;
	for (i = 0; i < lsh_num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(args);
	}
	return (lsh_launch(args));
}

void	lsh_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	do {
		printf("> ");
		line = lsh_read_line();
		args = lsh_split_line(line);
		status = lsh_execute(args);
		free(line);
		free(args);
	} while (status);
}


int	main(int argc, char *argv[])
{
	lsh_loop();
	return (EXIT_SUCCESS);
}