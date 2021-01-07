#include "../../includes/minishell.h"

void ff_to_out(t_args *x, int fd, int temp_fd)
{
	int id;
	char *command = "/usr/bin/";

	id = fork();
	command = ft_strjoin(command, *(x->argv));
	if (id == 0)
	//child process
	{
		dup2(fd, 0);
		if (x->orig_imp == 0)
			execv(command, x->argv);
		else
		{
			free(command);
			x->env = implement(x->argv, x->env, x->orig_imp);
		}
		return ;
	}
	//parent process
	waitpid(id, NULL, 0);
	free(command);
	dup2(temp_fd, 0);
}

void ff_to_pipe(t_args *x, int fdi)
{
	int id;
	int fd[2];
	char *command = "/usr/bin/";

	pipe(fd);
	id = fork();
	command = ft_strjoin(command, *(x->argv));
	if (id == 0)
	//child process
	{
		dup2(fdi, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		if (x->orig_imp == 0)
			execv(command, x->argv);
		else
		{
			free(command);
			x->env = implement(x->argv, x->env, x->orig_imp);
		}
		return ;
	}
	//parent process
	waitpid(id, NULL, 0);
	free(command);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}
	
void ff_to_file(t_args *x, int fdi, int temp_fd)
{
	int id;
	int fd;
	char *command = "/usr/bin/";

	if (x->write_append == 0)
		fd = open(x->red_files, O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	else
		fd = open(x->red_files, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	id = fork();
	command = ft_strjoin(command, *(x->argv));
	if (id == 0)
	//child process
	{
		dup2(fdi, 0);
		dup2(fd, 1);
		if (x->orig_imp == 0)
			execv(command, x->argv);
		else
		{
			free(command);
			x->env = implement(x->argv, x->env, x->orig_imp);
		}
		execv(command, (x->argv));
		return ;
	}
	//parent process
	waitpid(id, NULL, 0);
	free(command);
	dup2(temp_fd, 0);
}

void from_file(t_args *x, int temp_fd)
{
	int fd;

	fd = open(x->inp_files, O_RDONLY);
	if (x->out_pipe_red == 0)
		ff_to_out(x, fd, temp_fd);
	else if (x->out_pipe_red == 1)
		ff_to_pipe(x, fd);
	else
		ff_to_file(x, fd, temp_fd);
	close (fd);
}
