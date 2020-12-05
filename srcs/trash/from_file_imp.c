#include "../../includes/minishell.h"

void ff_to_out_imp(t_args *x, int fd)
{
	dup2(fd, 0);
	x->env = implement(x->args, x->env, x->orig_imp);
	dup2(x->temp_fd_0, 0);
}

void ff_to_pipe_imp(t_args *x, int fdi)
{
	int fd[2];

	pipe(fd);
	dup2(fdi, 0);
	dup2(fd[1], 1);
	x->env = implement(x->args, x->env, x->orig_imp);
	dup2(x->temp_fd_1, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}
	
void ff_to_file_imp(t_args *x, int fdi)
{
	int fd;

	if (x->write_append == 0)
		fd = open(x->red_file, O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	else
		fd = open(x->red_file, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	dup2(fdi, 0);
	dup2(fd, 1);
	x->env = implement(x->args, x->env, x->orig_imp);
	dup2(x->temp_fd_1, 1);
	close(fd);
	dup2(x->temp_fd_0, 0);
}

void from_file_imp(t_args *x)
{
	int fd;

	fd = open(x->inp_file, O_RDONLY);
	if (x->out_pipe_red == 0)
		ff_to_out_imp(x, fd);
	else if (x->out_pipe_red == 1)
		ff_to_pipe_imp(x, fd);
	else
		ff_to_file_imp(x, fd);
	close(fd);
}
