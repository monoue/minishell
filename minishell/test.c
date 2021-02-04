#include "minishell.h"

#define SYNTAX_VALID			-1
#define SYNTAX_QUOTED_WRONGLY	-2

int main()
{
	int		ret;
	char	*strs[] = {
		"; ls hoge",
		"ls ; |",
		"ls > |",
		"ls > < hoge",
		"ls >",
		NULL
	};
	size_t	index = 0;
	const char *newline = "NEWLINE";

	char **words;
	while (strs[index])
	{
		words = split_command_line(strs[index]);
		if ((ret = check_syntax(strs[index])) != SYNTAX_VALID)
		{
			if (!words[ret])
			{
				DSZ(index);
				DS(newline);
			}
			else
			{
				DSZ(index);
				DS(words[ret]);
			}
		}
		index++;
	}
}
