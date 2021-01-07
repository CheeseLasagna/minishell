/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_imp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:09:51 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/07 15:09:57 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_to_pipe_imp(t_args *x)
{
	int fd[2];

	pipe(fd);
	dup2(fd[1], 1);
	x->env = implement(x->argv, x->env, x->orig_imp);
	dup2(x->temp_fd_1, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}

void	write_to_stdout_imp(t_args *x)
{
	x->env = implement(x->argv, x->env, x->orig_imp);
	dup2(x->temp_fd_0, 0);
}

void	write_to_file_imp(t_args *x)
{
	int fd;

	fd = find_descriptor(x);
	dup2(fd, 1);
	x->env = implement(x->argv, x->env, x->orig_imp);
	dup2(x->temp_fd_1, 1);
	dup2(x->temp_fd_0, 0);
}

void	exec_command_imp(t_args *x)
{
	if (x->write_to == 1)
		write_to_pipe_imp(x);
	else if (x->write_to == 2)
		write_to_file_imp(x);
	else
		write_to_stdout_imp(x);
}
