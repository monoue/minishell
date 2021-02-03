#include "minishell.h"

int main()
{
	char *str = "hoge \' \" hoge \"  \'  ||;;<<>>";
	char **strs = split_command_line(str);
	size_t	index = 0;
	while (strs[index])
	{
		DS(strs[index]);
		index++;
	}
}
