/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_result_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:07:49 by monoue            #+#    #+#             */
/*   Updated: 2021/01/20 16:30:05 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put_result.h"

static void	put_c_null_case_fd(char *output, int fd)
{
	size_t			index;
	const size_t	output_len = ft_strlen(output);

	index = 0;
	while (index < output_len)
	{
		if (output[index] == '1')
			ft_putchar_fd('\0', fd);
		else
			ft_putchar_fd(' ', fd);
		index++;
	}
}

static char	*cut_by_precision(char *output, int prec)
{
	char	*cut_output;

	if (!output)
		return (NULL);
	cut_output = ft_substr(output, 0, prec);
	SAFE_FREE(output);
	return (cut_output);
}

static char	*free_and_strdup_null(char *new_target)
{
	SAFE_FREE(new_target);
	return (ft_strdup(""));
}

static char	*apply_precision(char *output, t_format_info *info)
{
	int	prec;
	int	margin;

	prec = info->precision;
	if (prec == NOT_SET)
		return (output);
	if (ft_strchr("diuxXp", info->conv_c) && prec == 0 && output[0] == '0')
		return (free_and_strdup_null(output));
	margin = prec - ft_strlen(output);
	if (ft_strchr("cs", info->conv_c) && margin <= 0)
		return (cut_by_precision(output, prec));
	if (ft_strchr("diup", info->conv_c) && margin >= 0)
	{
		if (output[0] == '-')
		{
			output[0] = '0';
			fill_output_with_zero(&output, margin + 1);
			output[0] = '-';
		}
		else
			fill_output_with_zero(&output, margin);
	}
	else if (ft_strchr("xX", info->conv_c) && margin > 0)
		fill_empty_with_zero(&output, margin, info);
	return (output);
}

int			put_result_fd(t_format_info *info, int fd)
{
	char	*output;
	size_t	output_len;
	int		margin;

	output = ft_strdup(info->value);
	output = apply_precision(output, info);
	if (info->conv_c == 'p')
		output = ft_strjoin_free_both(ft_strdup("0x"), output);
	margin = info->min_width - (int)ft_strlen(output);
	if (margin > 0)
		apply_margin(&output, margin, info);
	output_len = ft_strlen(output);
	if (info->c_null == true)
		put_c_null_case_fd(output, fd);
	else
		ft_putstr_fd(output, fd);
	SAFE_FREE(output);
	SAFE_FREE(info->value);
	SAFE_FREE(info);
	return (output_len);
}
