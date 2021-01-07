/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 21:08:56 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/06 20:19:49 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SPEC_SYMBOLS ";$\'\" \\|<>\0"
# define FILE_SPEC_SYMBOLS "; |<>\0"
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include "libft.h"

int		exit_status;
char	*line;

typedef struct	s_args
{
	char	**argv;
	int		argc;
	char	**env;
	int		write_to; // если |, то 1, если > или >>, то 2
	char	**red_files; //output file если встретился >
	int		red_count;
	char	**inp_files; //input file если встретился <
	int		inp_count;
	int		orig_imp;
	int		*write_append; // если встретился >. write(>) - 1, append(>>) - 2
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
** structure.c
*/
int		init_arg_struct(t_args *args);
void	free_arg_struct(t_args *args);
/*
** parser.c
*/
int		clean_last_whitespace(t_args *args);
int		parser(t_args *args, char *input_str);
/*
** parser_env.c
*/
int		parse_env(t_args *args, char ***strarr, int *strnum, char **str);
char	*find_env_value(t_args *args, char *env_name, int i);
char	*parse_env_name(char **str);
/*
** parser_escape_symbol.c
*/
int		replace_escape_symbol(char **dst, char **str);
int		replace_escape_symbol_in_doublequotes(char **dst, char **str);
/*
** parser_quotes.c
*/
int		add_doublequoted_str_to_str(t_args *args, char ***strarr, int *strnum, char **str);
int		add_signalquoted_str_to_str(char **dst, char **str);
/*
** parser_redirect.c
*/
int		parse_redirect(t_args *args, char ***strarr, int *strnum, char **str);
/*
** parser_semicolon.c
*/
int		check_semicolon(t_args *args, char **str);
/*
** pasrer_spaces.c
*/
int		parse_spaces(char ***strarr, int *strnum, char **str);
/*
** parser_pipe.c
*/
int		parse_pipe(t_args *args);
/*
** cd.c
*/
char	**cd(char **args, char **env);

/*
** echo.c
*/
void	echo(char **args);
/*
** env.c
*/
void	envp(char **env);
/*
** exit.c
*/
void	my_exit(char **arg, char **env);
/*
** export.c
*/
char	**export(char **args, char **env);
/*
** export_unset_2.c
*/
int		check_args_export(char *arg);
int		keylen(char *key);
char	**unset(char **args, char **env);
/*
** pwd.c
*/
void	pwd(void);

/*
** from_file.c (trash)
*/
void	from_file(t_args *x);
/*
** from_file_imp.c (trash)
*/
void	from_file_imp(t_args *x);
/*
** exec.c
*/
void	exec_command(t_args *x);
int     find_descriptor(t_args *x);
/*
** exec_imp.c
*/
void exec_command_imp(t_args *x);

/*
** exec_signals.c
*/
void sigint_skip(int signum);
void sigquit_skip(int signum);
void sigint_child(int signum);
void sigquit_child(int signum);

/*
** exec_utils.c
*/
void clear_struct(t_args *x);
int find_descriptor(t_args *x);
int check_fork(t_vars *vars, int temp_fd_0);
int check_pipe_fork(t_vars *vars);

/*
** exec_utils.c
*/
int try_execve(char **args, char **env);

/*
** implement.c
*/
char **implement(char **args, char **env, int imp);

/*
** main.c
*/
void sigint(int sig);
void sigquit(int sig);
#endif
