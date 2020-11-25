#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

typedef struct s_args
{
	char **args;
	char *red_file;
	char *inp_file;
	int	write_append;
	int	out_pipe_red;
}				t_args;

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *pointer;
	char *assign;

	if (!s1 || !s2)
		return (NULL);
	pointer = (char*)malloc(strlen(s1) + strlen(s2) + 1);
	assign = pointer;
	if (pointer == NULL)
		return (NULL);
	while (*s1)
		*assign++ = *s1++;
	while (*s2)
		*assign++ = *s2++;
	*assign = '\0';
	return (pointer);
}

void write_to_pipe(char **args)
{
	int id;
	int fd[2];
	char *command = "/usr/bin/";

	pipe(fd);
	id = fork();
	command = ft_strjoin(command, *args);
	if (id == 0)
	//child process
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execv(command, args);
		return ;
	}
	//parent process
	waitpid(id, NULL, 0);
	free(command);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}

void write_to_stdout(char **args, int temp_fd)
{
	int id;
	char *command = "/usr/bin/";

	id = fork();
	command = ft_strjoin(command, *args);
	if (id == 0)
	//child process
	{
		execv(command, args);
		return ;
	}
	//parent process
	waitpid(id, NULL, 0);
	free(command);
	dup2(temp_fd, 0);
}
	
void write_to_file(t_args x, int temp_fd)
{
	int id;
	int fd;
	int len;
	char *command = "/usr/bin/";
	

	if (x.write_append == 0)
		fd = open(x.red_file, O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	else
		fd = open(x.red_file, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	id = fork();
	command = ft_strjoin(command, *(x.args));
	if (id == 0)
	//child process
	{
		dup2(fd, 1);
		execv(command, x.args);
		return ;
	}
	//parent process
	waitpid(id, NULL, 0);
	free(command);
	dup2(temp_fd, 0);
}

void ff_to_out(t_args x, int fd, int temp_fd);
void ff_to_pipe(t_args x, int fdi);
void ff_to_file(t_args x, int fdi, int temp_fd);

void from_file(t_args x, int temp_fd)
{
	int fd;

	fd = open(x.inp_file, O_RDONLY);
	if (x.out_pipe_red == 0)
		ff_to_out(x, fd, temp_fd);
	else if (x.out_pipe_red == 1)
		ff_to_pipe(x, fd);
	else
		ff_to_file(x, fd, temp_fd);
	close (fd);
}

void ff_to_out(t_args x, int fd, int temp_fd)
{
	int id;
	char *command = "/usr/bin/";

	id = fork();
	command = ft_strjoin(command, *(x.args));
	if (id == 0)
	//child process
	{
		dup2(fd, 0);
		execv(command, x.args);
		return ;
	}
	//parent process
	waitpid(id, NULL, 0);
	free(command);
	dup2(temp_fd, 0);
}

void ff_to_pipe(t_args x, int fdi)
{
	int id;
	int fd[2];
	char *command = "/usr/bin/";

	pipe(fd);
	id = fork();
	command = ft_strjoin(command, *(x.args));
	if (id == 0)
	//child process
	{
		dup2(fdi, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execv(command, (x.args));
		return ;
	}
	//parent process
	waitpid(id, NULL, 0);
	free(command);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}
	
void ff_to_file(t_args x, int fdi, int temp_fd)
{
	int id;
	int fd;
	char *command = "/usr/bin/";

	if (x.write_append == 0)
		fd = open(x.red_file, O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	else
		fd = open(x.red_file, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	id = fork();
	command = ft_strjoin(command, *(x.args));
	if (id == 0)
	//child process
	{
		dup2(fdi, 0);
		dup2(fd, 1);
		execv(command, (x.args));
		return ;
	}
	//parent process
	waitpid(id, NULL, 0);
	free(command);
	dup2(temp_fd, 0);
}

void exec_command(t_args x, int flag, int temp_fd)
{
	
	if (flag == 1)
		write_to_pipe(x.args);
	else if (flag == 2)
		write_to_file(x, temp_fd);
	else if (flag == 3)
		from_file(x, temp_fd); 
	else
		write_to_stdout(x.args, temp_fd);
}
	
int main()
{
	t_args my_args;
	int temp_fd = dup(0);
	printf("temp_fd = %d\n", temp_fd);
	char *first[] = {"ls", "-l", NULL};
	char *second[] = {"grep", "proc2.c", NULL};
	char *third[] = {"ls", NULL};
	char *forth[] = {"grep", "main.c", NULL};
	char *fifth[] = {"echo", "testtesttest", NULL};
	char *sixth[]= {"echo", "hello there blyat", NULL};
	char *eigth[]= {"grep", "test", NULL};
	char *tenth[] ={"sort", NULL};

/*	//first
	my_args.args = first;
	exec_command(my_args, 1, temp_fd);
	//second
	my_args.args = second;
	exec_command(my_args, 0, temp_fd);
	//third
	my_args.args = third;
	exec_command(my_args, 1, temp_fd);
	//forth
	my_args.args = forth;
	exec_command(my_args, 0, temp_fd);
	//fifth
	my_args.args = fifth;
	exec_command(my_args, 0, temp_fd);*/
	//sixth
/*	my_args.args = sixth;
	my_args.red_file = "filejeka.txt";
	my_args.write_append = 0;
	exec_command(my_args, 2, temp_fd);
	//seventh
	my_args.args = sixth;
	my_args.red_file = "filejeka2.txt";
	my_args.write_append = 1;
	exec_command(my_args, 2, temp_fd);*/

/*	//eigth
	my_args.args = eigth;
	my_args.inp_file = "input.txt";
	my_args.out_pipe_red = 0;
	exec_command(my_args, 3, temp_fd);*/

/*	//ninth
	my_args.args = eigth;
	my_args.inp_file = "input.txt";
	my_args.red_file = "filejeka.txt";
	my_args.out_pipe_red = 2;
	my_args.write_append = 0;
	exec_command(my_args, 3, temp_fd);
	//ninth
	my_args.args = eigth;
	my_args.inp_file = "input.txt";
	my_args.red_file = "filejeka2.txt";
	my_args.out_pipe_red = 2;
	my_args.write_append = 1;
	exec_command(my_args, 3, temp_fd);*/

	//tenth
	my_args.args = eigth;
	my_args.inp_file = "input.txt";
	my_args.out_pipe_red = 1;
	exec_command(my_args, 3, temp_fd);

	my_args.args = tenth;
	exec_command(my_args, 0, temp_fd);
	
	
	return (0);
}
