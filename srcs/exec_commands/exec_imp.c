#include "../../includes/minishell.h"

void write_to_pipe_imp(t_args *x)
{
	int fd[2];

	pipe(fd);
	dup2(fd[1], 1);
	x->env = implement(x->args, x->env, x->orig_imp);
	dup2(x->temp_fd_1, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}

void write_to_stdout_imp(t_args *x)
{
	x->env = implement(x->args, x->env, x->orig_imp);
	dup2(x->temp_fd_0, 0);
}
	
void write_to_file_imp(t_args *x)
{
	int fd;
	

	/*if (x->write_append == 0)
		fd = open(x->red_file, O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	else
		fd = open(x->red_file, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);*/
	fd = find_descriptor(x);
	dup2(fd, 1);
	x->env = implement(x->args, x->env, x->orig_imp);
	dup2(x->temp_fd_1, 1);
	dup2(x->temp_fd_0, 0);
}

void exec_command_imp(t_args *x, int flag)
{
	if (flag == 1)
		write_to_pipe_imp(x);
	else if (flag == 2)
		write_to_file_imp(x);
//	else if (flag == 3)
	//	from_file_imp(x); 
	else
		write_to_stdout_imp(x);
}