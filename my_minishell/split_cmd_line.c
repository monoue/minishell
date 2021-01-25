#include "minishell.h"

static bool		is_symbol(char c)
{
	return (ft_strchr("><|", c));
}

static size_t	count_words(char const *str)
{
	size_t	index;
	size_t	words_num;

	index = 0;
	while (str[index] != '\0' && str[index] == ' ')
		index++;
	words_num = 0;
	while (str[index] != '\0')
	{
		if (ft_strncmp(&str[index], ">>", 2) == 0)
			index += 2;
		else if (is_symbol(str[index]))
			index++;
		else
			while (str[index] != '\0' && !is_symbol(str[index]) && str[index] != ' ')
				index++;
		while (str[index] != '\0' && str[index] == ' ')
			index++;
		words_num++;
	}
	return (words_num);
}


static char		*cut_out_one_word(const char *str, size_t *index)
{
	size_t			start;

	while (str[*index] && str[*index] == ' ')
		(*index)++;
	start = *index;
	if (ft_strncmp(&str[*index], ">>", 2) == 0)
		*index += 2;
	else if (is_symbol(str[*index]))
		(*index)++;
	else
		while (str[*index] != '\0' && !is_symbol(str[*index]) && str[*index] != ' ')
			(*index)++;
	return (ft_substr(str, start, *index - start));
}

char			**split_cmd_line(char const *str)
{
	char	**words;
	size_t	words_num;
	size_t	index;
	size_t	w_i;

	if (!str)
		return (NULL);
	words_num = count_words(str);
	words = ft_calloc((words_num + 1), sizeof(*words));
	if (!words)
		return (NULL);
	w_i = 0;
	index = 0;
	while (w_i < words_num)
	{
		words[w_i] = cut_out_one_word(str, &index);
		if (!words[w_i])
		{
			ft_free_split(words);
			return (NULL);
		}
		w_i++;
	}
	return (words);
}

// void	print_strs(char **str)
// {
// 	size_t	index;

// 	index = 0;
// 	while (str[index])
// 	{
// 		DS(str[index]);
// 		index++;
// 	}
// }

// int main()
// {

	// print_strs(split_cmd_line("hoge | > ls | wc"));
	// print_strs(split_cmd_line("hoge|>ls|wc"));
	// print_strs(split_cmd_line("ls | hoge | > ls | wc"));
	// print_strs(split_cmd_line("ls|hoge|>ls|wc"));
	// print_strs(split_cmd_line("ls | wc | hoge | > ls | wc"));
	// print_strs(split_cmd_line("ls|wc|hoge|>ls|wc"));
	// print_strs(split_cmd_line("ls | >>> ls | wc"));
	// print_strs(split_cmd_line("ls|>ls|wc"));
	// print_strs(split_cmd_line("ls | | > ls | wc"));
	// print_strs(split_cmd_line("ls||>ls|wc"));
	// print_strs(split_cmd_line(""));
// }