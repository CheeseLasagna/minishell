/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:09:28 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/07 15:09:32 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_struct(t_args *x)
{
	if (x->argv)
		ft_strarrclear(&(x->argv));
	if (x->red_files)
		ft_strarrclear(&(x->red_files));
	if (x->inp_files)
		free(x->inp_files);
}

int		find_descriptor(t_args *x)
{
	char	**files;
	int		fd;
	int		*write_append;

	files = x->red_files;
	write_append = x->write_append;
	fd = 0;
	while (*files != NULL)
	{
		if (fd)
			close(fd);
		if (*write_append == 1)
			fd = open(*files, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		else
			fd = open(*files, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		files++;
		write_append++;
	}
	return (fd);
}

int		check_fork(t_vars *vars, int temp_fd_0)
{
	char *str;

	vars->id = fork();
	if (vars->id == -1)
	{
		str = strerror(errno);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		dup2(temp_fd_0, 0);
		close(vars->fdd);
		return (1);
	}
	return (0);
}

int		check_pipe_fork(t_vars *vars)
{
	char *str;

	if (pipe(vars->fd) == -1)
	{
		str = strerror(errno);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		return (1);
	}
	vars->id = fork();
	if (vars->id == -1)
	{
		str = strerror(errno);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		close(vars->fd[0]);
		close(vars->fd[1]);
		return (1);
	}
	return (0);
}
