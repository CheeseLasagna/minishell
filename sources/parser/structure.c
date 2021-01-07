/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:13:08 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/06 20:14:13 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_arg_struct(t_args *args)
{
	args->argc = 0;
	if (!(args->argv = ft_calloc(sizeof(char *), args->argc + 2)))
		return (0);
	args->write_to = 0;
	args->red_count = 0;
	if (!(args->red_files = ft_calloc(sizeof(char *), args->argc + 2)))
		return (0);
	args->inp_count = 0;
	if (!(args->inp_files = ft_calloc(sizeof(char *), args->argc + 2)))
		return (0);
	args->orig_imp = -1;
	if (!(args->write_append = ft_calloc(sizeof(int), args->red_count + 2)))
		return (0);
	args->out_pipe_red = -1;
	return (1);
}

void	free_arg_struct(t_args *args)
{
	free_strarr(args->argv);
	args->argv = NULL;
	free_strarr(args->red_files);
	args->red_files = NULL;
	free_strarr(args->inp_files);
	args->inp_files = NULL;
	free(args->write_append);
	args->write_append = NULL;
}
