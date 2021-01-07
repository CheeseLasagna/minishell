#include "../../includes/minishell.h"

void write_to_pipe(t_args *x)
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

void write_to_stdout(t_args *x, int temp_fd)
{
	int id;
	char *command = "/usr/bin/";

	id = fork();
	command = ft_strjoin(command, *(x->argv));
	if (id == 0)
	//child process
	{
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
	
void write_to_file(t_args *x, int temp_fd)
{
	int id;
	int fd;
	int len;
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
		dup2(fd, 1);
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

int check_command(char **args)
{
	if ((strncmp("echo", *args, ft_strlen(*args))) == 0)
		return (1);
	else if ((strncmp("cd", *args, ft_strlen(*args))) == 0)
		return (2);
	else if ((strncmp("pwd", *args, ft_strlen(*args))) == 0)
		return (3);
	else if ((strncmp("export", *args, ft_strlen(*args))) == 0)
		return (4);
	else if ((strncmp("unset", *args, ft_strlen(*args))) == 0)
		return (5);
	else if ((strncmp("env", *args, ft_strlen(*args))) == 0)
		return (6);
	else if ((strncmp("exit", *args, ft_strlen(*args))) == 0)
		return (7);
	else
		return (0);
}

char **exec_command(t_args *x, int flag, int temp_fd)
{
	x->orig_imp = check_command(x->argv);
	if (flag == 1)
		write_to_pipe(x);
	else if (flag == 2)
		write_to_file(x, temp_fd);
	else if (flag == 3)
		from_file(x, temp_fd); 
	else
		write_to_stdout(x, temp_fd);
}
