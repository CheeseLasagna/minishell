/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:31:33 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/06 19:37:39 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		add_signalquoted_str_to_str(char **dst, char **str)
{
	(*str)++;
	while (**str != '\0' && **str != '\'')
	{
		if (!(add_char_to_str(dst, **str)))
			return (0);
		(*str)++;
	}
	if (**str == '\0')
		(*str)--;
	return (1);
}

int		add_doublequoted_str_to_str(t_args *args, char ***strarr
									, int *strnum, char **str)
{
	int status;

	status = 1;
	(*str)++;
	while (**str != '\0' && **str != '\"')
	{
		if (**str == '\\')
			status = replace_escape_symbol_in_doublequotes(
								&((*strarr)[*strnum]), str);
		else if (**str == '$')
			status = parse_env(args, strarr, strnum, str);
		else
			status = add_char_to_str(&((*strarr)[*strnum]), **str);
		if (!status)
			return (0);
		(*str)++;
	}
	if (**str == '\0')
		(*str)--;
	return (1);
}
