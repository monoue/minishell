#include "minishell.h"

// どちらが先に現れるか
// not found も含め
typedef	enum {
	SINGLE,
	DOUBLE,
	NOT_EXIST	
}		t_quote;

size_t	count_quotes_sets(char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;
	char			quote;
	size_t			sets_num;

	sets_num = 0;
	index = 0;
	while (index < len)
	{
		if (str[index] == '\'' || str[index] == '\"')
		{
			quote = str[index];
			index++;
			while (index < len && str[index] != quote)
				index++;
			sets_num++;
		}
		index++;
	}
	return (sets_num);
}
 // 次、malloc。
// bool	has_quote_set(char *str)
// {
	
// }

// int	get_index(const char *str, char c)
// {
// 	size_t	index;

// 	index = 0;
// 	while (str[index] != '\0' && str[index] != c)
// 		index++;
// 	if (index == ft_strlen(str))
// 		return (NOT_FOUND);
// 	return (index);
// }

// size_t	is_set(char c)
// {

// }
// bool	has_quotes_set(char *str, char quote)
bool	has_quotes_set(char *str, char quote)
{
	const char		*tmp = ft_strchr(str, quote);
	const size_t	len = ft_strlen(tmp);

	if (len < 2)
		return (false);
	return (ft_strchr(&tmp[1], quote));
}


// int	trim_quotes(char **str)
// int	trim_quotes(char **str)
// char	*trim_quotes(char *str)
// {
// 	char		quote;
// 	// bool	is_quoted

// 	// quote = get_first_quote(*str);
// 	DC(quote);
// 	if (!quote)
// 		return (str)
	
	
	
	
// 	// if (has_single && has_double)

			
// }
char	get_first_quote(const char *str)
{
	const char *first_single = ft_strchr(str, '\'');
	const char *first_double = ft_strchr(str, '\"');

	if (!first_single && !first_double)
		return (0);
	if (first_single < first_double)
		return ('\'');
	return ('\"');
}

bool	has_quote(char *str)
{
	return (ft_strchr(str, '\'') || ft_strchr(str, '\"'));
}

// bool	is_quoted_wrongly(char *str)
// {
// 	char	quote;

// 	// if (!has_quote(str))
// 	// 	return (false);
// 	while (has_quote(str))
// 	{
// 		quote = get_first_quote(str);

// 	}

// 	return (false);
// }

// trim_quotes と is_quoted を分ける。

 // free の必要性も考える
 // 無理に int で返そうとしない。bool で、ダメなヤツだと判定する関数を別に作る。

// char	*trim_quotes(char **str)
// char	*get_quotes_trimmed_str(char *str)
// {
// 	// if (!has_quote(str))
// 	// 	return (str);
// 	// has_quotes_set
// 	// while (has_quotes_set)

// }

// free の関連で、返り値を返した方が、アドレスを渡していじるよりも良いように思われる。

int	main()
{
	char *str_ok_1 = "hoge\"hoge\""; // OK
	char *str_ok_2 = "hoge\'hoge\"\'"; // OK

	char *str_ng_1 = "hoge\"hoge"; // NG
	char *str_ng_2 = "hoge\'hoge\""; // NG
	DI(is_quoted_wrongly(str_ok_1));
	DI(is_quoted_wrongly(str_ok_2));
	DI(is_quoted_wrongly(str_ng_1));
	DI(is_quoted_wrongly(str_ng_2));
	// char	*trimmed_s;

	// DI(is_quoted_wrongly(str1));
	// if (has_quote(str1))
	// {
	// 	if (is_quoted_wrongly(str1))
	// 		return (EXIT_FAILURE);
		
	// }
	// trimmed_s = get_quotes_trimmed_str(str1);

	// if (!has_quote(str1))
	// 	return 
	// trim_quotes
	// DI(has_quotes_set("hoge\"hoge\"", '\"'));
	// DI(has_quotes_set("hoge\"hoge", '\"'));
	// DI(has_quotes_set("hoge\"hoge\"", '\"'));
	// const char *str = "hoge\"fuga\'1\'2\"";
	// DP(ft_strchr(str, '\"')); // 早い方が小さい
	// DP(ft_strchr(str, '\''));
	// DI(ft_strchr(str, '\"') > ft_strchr(str, '\''));
}