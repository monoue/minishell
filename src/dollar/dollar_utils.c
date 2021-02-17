/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:58:09 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/17 11:03:06 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*go_parse_dq(char *argv, t_list *envp)
{
	char	**tmp;
	char	*str;
	int		j;
	int		tmp_num;
	char	*value;
	char	*final;

	j = 0;
	flag_single_in_dq = 1;
	tmp_num = count_command_line_words(argv);
	tmp = malloc(sizeof(*tmp) * (tmp_num + 1000));
	str = NULL;
	value = NULL;
	final = NULL;
	tmp = do_parse2(argv);
	j = 0;
	while (tmp[j])
	{
		if (dollar_or_not(tmp[j], '$'))
			str = replace_dollar_value(tmp[j], envp, 1);
		else
			str = ft_strdup(tmp[j]);
		value = ft_strnjoin_free(value, str, ft_strlen(str));
		free(str);
		j++;
	}
	final = remove_escape(value);
	free(value);
	ft_free_split(tmp);
	return (final);
}

int		is_char_or_not(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*replace_word(const char *head, char *cut_word,
		const char *word, int i)
{
	char	*ret;
	int		length;
	size_t	j;
	size_t	f;

	length = ft_strlen(head) + ft_strlen(word) - ft_strlen(cut_word);
	if (!(ret = malloc(length + 1)))
		return (NULL);
	j = 0;
	f = 0;
	while (i < length)
	{
		if (head[i] == '\'')
		{
			ret[i++] = head[f++];
			f = f + ft_strlen(cut_word);
			while (j < ft_strlen(word))
				ret[i++] = word[j++];
			ret[i++] = head[f++];
		}
		ret[i++] = head[f++];
	}
	ret[i] = '\0';
	return (ret);
}

char	*put_single_quotes(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	if (!(tmp = malloc(ft_strlen(str) + 2)))
		exit_err_msg(MALLOC_ERR);
	i = 0;
	j = 0;
	tmp[j] = '\'';
	j++;
	while (str[i])
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\'';
	j++;
	return (tmp);
}

bool	ft_isascii1(int n)
{
	return (n != '\'' && n != '\"' && n != '$' && n != '/' && n != '\\');
}
