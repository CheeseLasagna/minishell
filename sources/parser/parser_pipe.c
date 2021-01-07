/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:38:05 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/06 19:36:34 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_pipe(t_args *args)
{
	if (!(*(args->argv)))
	{
		ft_putstr("bash: syntax error near unexpected token `|'\n");
		exit_status = 2;
		return (2);
	}
	args->write_to = 1;
	clean_last_whitespace(args);
	exec_command(args);
	free_arg_struct(args);
	return (init_arg_struct(args));
}
