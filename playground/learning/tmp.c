#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	size_t	index;

	index = 0;
	while (env[index])
	{
		printf("%s\n", env[index]);
		index++;
	}
}