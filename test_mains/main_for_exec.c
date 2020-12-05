#include "../includes/minishell.h"

int main(int argc, char **argv, char **environ)
{
	t_args my_args;
	my_args.temp_fd_0 = dup(0);
	my_args.temp_fd_1 = dup(1);

	char *first[] = {"echo", "privet", NULL};
	char *redirect[] = {"file1", "file2", "file3", NULL};
	int wr_ap[] = {0, 1, 0};
//	char *second[] = {"grep", "proc2.c", NULL};
	my_args.env = convert_array(environ);

/*	//first
	my_args.args = first;
	exec_command(my_args, 1, temp_fd);*/

	//first
	my_args.args = first;
	my_args.red_file = redirect;
	my_args.write_append = wr_ap;
	exec_command(&my_args, 2);
	
	return (0);
}