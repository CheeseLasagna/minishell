/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_semicolon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:45:00 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/06 19:45:08 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_semicolon(t_args *args, char **str)
{
	(*str)++;
	if (!(*(args->argv)) || **str == ';')
	{
		ft_putstr("bash: syntax error near unexpected token ");
		if (**str == ';')
			ft_putstr("`;;'\n");
		else
			ft_putstr("`;'\n");
		exit_status = 2;
		return (2);
	}
	(*str)--;
	clean_last_whitespace(args);
	exec_command(args);
	free_arg_struct(args);
	return (init_arg_struct(args));
}
