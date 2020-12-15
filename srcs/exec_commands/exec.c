#include "../../includes/minishell.h"

int check_pipe_fork(t_vars *vars)
{
	char *str;

	if(pipe(vars->fd) == -1)
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

void write_to_pipe(t_args *x)
{
	/*int id;
	int rrr;
	int fd[2];
	char *str = "/usr/bin/";*/
	t_vars vars;

	vars.str = "/usr/bin/";
	if (check_pipe_fork(&vars) == 1)
		return ;
	/*if(pipe(fd) == -1)
	{
		str = strerror(errno);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		return ;
	}
	id = fork();
	if (id == -1)
	{
		str = strerror(errno);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		close(fd[0]);
		close(fd[1]);
		return ;
	}*/
	vars.str = ft_strjoin(vars.str, *(x->args));
	if (vars.id == 0)
	//child process
	{
		dup2(vars.fd[1], 1);
		close(vars.fd[0]);
		close(vars.fd[1]);
		vars.ex_res = execve(vars.str, x->args, x->env);
		if (vars.ex_res == -1)
			exit(127);
	}
	//parent process
	waitpid(vars.id, &vars.ex_res, 0);
	if (WIFEXITED(vars.ex_res))
		exit_status = WEXITSTATUS(vars.ex_res);
	free(vars.str);
	dup2(vars.fd[0], 0);
	close(vars.fd[1]);
	close(vars.fd[0]);
}

int check_fork(t_vars *vars, int temp_fd_0)
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

void write_to_stdout(t_args *x)
{
	/*int rrr;
	int id;
	char *str = "/usr/bin/";*/
	t_vars vars;

	vars.str = "/usr/bin/";
	if (check_fork(&vars, x->temp_fd_0) == 1)
		return ;
	/*id = fork();
	if (id == -1)
	{
		str = strerror(errno);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		dup2(x->temp_fd_0, 0);
		return ;
	}*/
	vars.str = ft_strjoin(vars.str, *(x->args));
	if (vars.id == 0)
	//child process
	{
		vars.ex_res = execve(vars.str, x->args, x->env);
		if (vars.ex_res == -1)
			exit(127);
	}
	//parent process
	waitpid(vars.id, &vars.ex_res, 0);
	if (WIFEXITED(vars.ex_res))
		exit_status = WEXITSTATUS(vars.ex_res);
	free(vars.str);
	dup2(x->temp_fd_0, 0);
}

int find_descriptor(t_args *x)	
{
	char **files;
	int fd;
	int *write_append;

	files = x->red_file;
	write_append = x->write_append;
	fd = 0;	
	while (*files != NULL)
	{
		if (fd)
			close(fd);
		if (*write_append == 0)
			fd = open(*files, O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
		else
			fd = open(*files, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
		files++;
		write_append++;
	}
	return (fd);
}
void write_to_file(t_args *x)
{
	/*int id;
	int fdd;
	int rrr;
	char *str = "/usr/bin/";*/
	t_vars vars;

/*	if (x->write_append == 0)
		fd = open(x->red_file, O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	else
		fd = open(x->red_file, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);*/
	vars.str = "/usr/bin/";
	vars.fdd = find_descriptor(x);
	if (check_fork(&vars, x->temp_fd_0) == 1)
		return ;
	/*id = fork();
	if (id == -1)
	{
		str = strerror(errno);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		close(fdd);
		dup2(x->temp_fd_0, 0);
		return ;
	}*/
	vars.str = ft_strjoin(vars.str, *(x->args));
	if (vars.id == 0)
	//child process
	{
		dup2(vars.fdd, 1);
		close(vars.fdd);
		vars.ex_res = execve(vars.str, x->args, x->env);
		if (vars.ex_res == -1)
			exit(127);
	}
	//parent process
	waitpid(vars.id, &vars.ex_res, 0);
	if (WIFEXITED(vars.ex_res))
		exit_status = WEXITSTATUS(vars.ex_res);
	free(vars.str);
	close(vars.fdd);
	dup2(x->temp_fd_0, 0);
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

void exec_command(t_args *x, int flag)
{
	exit_status = 0;
	x->orig_imp = check_command(x->args);
	if (x->orig_imp != 0)
		exec_command_imp(x, flag);
	else
	{
		if (flag == 1)
			write_to_pipe(x);
		else if (flag == 2)
			write_to_file(x);
		//else if (flag == 3)
			//from_file(x); 
		else
			write_to_stdout(x);
	}
}
