/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:19:29 by monoue            #+#    #+#             */
/*   Updated: 2021/02/03 12:19:39 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_quotes(char const *str, size_t *index)
{
	char	quote;

	quote = str[*index];
	(*index)++;
	while (str[*index] && str[*index] != quote)
		(*index)++;
	(*index)++;
}
