/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:13:18 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/07 02:54:02 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_spaces(char ***strarr, int *strnum, char **str)
{
	while ((*(*str + 1)) == ' ')
		(*str)++;
	if (*strnum == 0 || (*strarr)[*strnum][0] != '\0')
		return (add_empty_str_in_strarr(strarr, strnum));
	return (1);
}
