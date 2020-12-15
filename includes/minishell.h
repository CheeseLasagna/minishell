#ifndef MINISHELL 
# define MINISHELL 
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h> //delete later

# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

int exit_status;

typedef struct	s_args
{
	char	**args;
	char	**env;
	char	**red_file; //output file если встретился >
	char	*inp_file; //input file если встретился <
	int		orig_imp;
	int		*write_append; // если встретился >. write(>) - 0, append(>>) - 1
	int		out_pipe_red; //куда записывать если встретился < .  stdout - 0
						  //pipe - 1(если после < встреился |),
						  //redirect - 2(если после < встретился > или >>, также поменять write_append)
	int		temp_fd_0;
	int		temp_fd_1;
}               t_args;

typedef struct	s_vars
{
	int id;
	int fd[2];
	int fdd;
	int ex_res;
	char *str;
}				t_vars;

/*
**BUILTIN IMPLEMENTATIONS
*/
char	**cd(char **args, char **env);
void	echo(char **args);
void	envp(char **env);
void	my_exit(char **arg, char **env);
char	**export(char **args, char **env);
//int		find_doub_array_len(char **env);
int		check_args_export(char *arg);
int		keylen(char *key);
void	pwd();
char	**unset(char **args, char **env);

void    free_arrah(char **env);
char    **convert_array(char **args);


int     ft_strarrlen(char **strarr);
int     ft_strarrclear(char ***strarrp);
/*
**EXEC COMMANDS
*/
void from_file(t_args *x);
void from_file_imp(t_args *x);
void exec_command(t_args *x, int flag);
void exec_command_imp(t_args *x, int flag);
char **implement(char **args, char **env, int imp);
int find_descriptor(t_args *x);


#endif
