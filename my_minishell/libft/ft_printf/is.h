/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:18:28 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 13:18:29 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_H
# define IS_H

# include <stdbool.h>
# include <stdarg.h>

bool	is_of_chars(const unsigned int c, int argc, ...);
bool	isconversion_c(const unsigned int c);

#endif
