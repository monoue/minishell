#include "minishell.h"

void	print_strs(char **strs)
{
	size_t	index = 0;
	while (strs[index])
	{
		DS(strs[index])	;
		index++;
	}
}

int main(int argc, char *argv[])
{
/*
** is_quoted_wrongly test
*/
	// char	*str1 = "\"\\\"\"";
	// char	*str2 = " \" hoge \" ";
	// char	*str3 = "   \\\"   \"  \"        ";
	// char	*str4 = "   \\\"   \"  \"  \"      ";

	// char	**strs1 = split_command_line(str1);
	// char	**strs2 = split_command_line(str2);
	// char	**strs3 = split_command_line(str3);
	// char	**strs4 = split_command_line(str4);

	// DS(str1);
	// DI(is_quoted_wrongly(str1));
	// DS(str2);
	// DI(is_quoted_wrongly(str2));
	// DS(str3);
	// DI(is_quoted_wrongly(str3));
	// DS(str4);
	// DI(is_quoted_wrongly(str4));

/*
** split_command_line test
*/
	// char	*str1 = "\"\\\"\"";
	// char	*str2 = " \" hoge \" ";
	// char	*str3 = "   \\\"   \"  \"        ";
	// char	*str4 = "   \\\"   \"  \"  \"      ";
	// char	*str5 = " \'  \\\"   \" $yay  \"   \' hoge    ";
	// char	*str6 = " \'  \\\"   \" $  \"   \' hoge    ";

	// char	**strs1 = split_command_line(str1);
	// char	**strs2 = split_command_line(str2);
	// char	**strs3 = split_command_line(str3);
	// char	**strs4 = split_command_line(str4);
	// char	**strs5 = split_command_line(str5);
	// char	**strs6 = split_command_line(str6);

	(void)argc;
	(void)argv;
	// if (argc > 1)
	// {
	// 	char	**strs_input = split_command_line(argv[1]);
	// 	DS(argv[1]);
	// 	print_strs(strs_input);
	// }
	// char	**strs4 = split_command_line(str4);
	// DS(str1);
	// print_strs(strs1);
	// DS(str2);
	// print_strs(strs2);
	// DS(str3);
	// print_strs(strs3);
	// DS(str4);
	// print_strs(strs4);
	// DS(str5);
	// print_strs(strs5);
	// DS(str6);
	// print_strs(strs6);
	// DI(is_quote_char('\''));
	// DI(is_quote_char('\"'));
/*
** ft_atoi test
*/
	DS(remove_quotes("hoge\"  hoge  \"hoge"));
}
