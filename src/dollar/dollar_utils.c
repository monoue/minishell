/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:58:09 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/03 07:48:40 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*go_parse_dq(char *argv, t_list *envp, int j)
{
	char	**tmp;
	char	*str;
	char	*value;
	char	*final;

	g_flag = true;
	g_flag_escape_db = true;
	value = NULL;
	tmp = do_parse2(argv);
	while (tmp[j])
	{
		g_flag_dont = false;
		if (dollar_or_not(tmp[j], '$')
			&& (tmp[j][0] == '$' && tmp[j][1] != '?'))
			str = replace_dollar_value(tmp[j], envp);
		else
			str = ft_strdup(tmp[j]);
		final = return_final(str, tmp, j);
		value = ft_strnjoin_free(value, final, ft_strlen(final));
		SAFE_FREE(str);
		SAFE_FREE(final);
		j++;
	}
	ft_free_split(tmp);
	return (value);
}

char	*find_key_1(char *argv, t_list *envp)
{
	t_list	*tmp_list;
	char	*variable;
	char	*arg;

	arg = ft_strnjoin(&argv[1], "=", 1);
	tmp_list = envp;
	variable = NULL;
	while (tmp_list && tmp_list->next)
	{
		if (ft_strnequal((char*)tmp_list->content, arg, ft_strlen(arg)))
			variable = ft_strdup((char*)tmp_list->content);
		tmp_list = tmp_list->next;
	}
	SAFE_FREE(arg);
	return (variable);
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
