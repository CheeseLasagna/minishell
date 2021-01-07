/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:10:10 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/07 15:10:12 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_to_pipe(t_args *x)
{
	t_vars vars;

	if (check_pipe_fork(&vars) == 1)
		return ;
	signal(SIGINT, sigint_skip);
	signal(SIGQUIT, sigquit_skip);
	if (vars.id == 0)
	{
		signal(SIGINT, sigint_child);
		signal(SIGQUIT, sigquit_child);
		dup2(vars.fd[1], 1);
		close(vars.fd[0]);
		close(vars.fd[1]);
		vars.ex_res = try_execve(x->argv, x->env);
		if (vars.ex_res == -1)
			exit(127);
	}
	waitpid(vars.id, &vars.ex_res, 0);
	if (WIFEXITED(vars.ex_res))
		exit_status = WEXITSTATUS(vars.ex_res);
	dup2(vars.fd[0], 0);
	close(vars.fd[1]);
	close(vars.fd[0]);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}

void	write_to_stdout(t_args *x)
{
	t_vars vars;

	if (check_fork(&vars, x->temp_fd_0) == 1)
		return ;
	signal(SIGINT, sigint_skip);
	signal(SIGQUIT, sigquit_skip);
	if ((ft_strncmp("ping", *(x->argv), 4)) == 0)
		signal(SIGQUIT, SIG_IGN);
	if (vars.id == 0)
	{
		signal(SIGINT, sigint_child);
		signal(SIGQUIT, sigquit_child);
		vars.ex_res = try_execve(x->argv, x->env);
		if (vars.ex_res == -1)
			exit(127);
	}
	waitpid(vars.id, &vars.ex_res, 0);
	if (WIFEXITED(vars.ex_res))
		exit_status = WEXITSTATUS(vars.ex_res);
	dup2(x->temp_fd_0, 0);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}

void	write_to_file(t_args *x)
{
	t_vars vars;

	vars.fdd = find_descriptor(x);
	if (check_fork(&vars, x->temp_fd_0) == 1)
		return ;
	signal(SIGINT, sigint_skip);
	signal(SIGQUIT, sigquit_skip);
	if (vars.id == 0)
	{
		signal(SIGINT, sigint_child);
		signal(SIGQUIT, sigquit_child);
		dup2(vars.fdd, 1);
		close(vars.fdd);
		vars.ex_res = try_execve(x->argv, x->env);
		if (vars.ex_res == -1)
			exit(127);
	}
	waitpid(vars.id, &vars.ex_res, 0);
	if (WIFEXITED(vars.ex_res))
		exit_status = WEXITSTATUS(vars.ex_res);
	close(vars.fdd);
	dup2(x->temp_fd_0, 0);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}

int		check_command(char **args)
{
	if (!(*args))
		return (0);
	if (ft_strncmp("echo", *args, 5) == 0)
		return (1);
	else if (ft_strncmp("cd", *args, 3) == 0)
		return (2);
	else if (ft_strncmp("pwd", *args, 4) == 0)
		return (3);
	else if (ft_strncmp("export", *args, 7) == 0)
		return (4);
	else if (ft_strncmp("unset", *args, 6) == 0)
		return (5);
	else if (ft_strncmp("env", *args, 4) == 0)
		return (6);
	else if (ft_strncmp("exit", *args, 5) == 0)
		return (7);
	else
		return (0);
}

void	exec_command(t_args *x)
{
	x->orig_imp = check_command(x->argv);
	if (x->orig_imp != 0)
		exec_command_imp(x);
	else
	{
		exit_status = 0;
		if (x->write_to == 1)
			write_to_pipe(x);
		else if (x->write_to == 2)
			write_to_file(x);
		else
			write_to_stdout(x);
	}
}
