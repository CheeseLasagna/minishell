/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_escape_symbol.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:31:40 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/06 19:35:56 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		replace_escape_symbol(char **dst, char **str)
{
	(*str)++;
	if (**str)
		return (add_char_to_str(dst, **str));
	(*str)--;
	return (1);
}

int		replace_escape_symbol_in_doublequotes(char **dst, char **str)
{
	(*str)++;
	if (**str == '\\')
		return (add_char_to_str(dst, '\\'));
	else if (**str == '$')
		return (add_char_to_str(dst, '$'));
	else if (**str == '\"')
		return (add_char_to_str(dst, '\"'));
	(*str)--;
	add_char_to_str(dst, '\\');
	return (1);
}
