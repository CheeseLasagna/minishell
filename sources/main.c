/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 03:38:28 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/07 03:38:29 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int sig)
{
	(void)sig;
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
	write(1, "\n> ", 3);
}

void	sigquit(int sig)
{
	(void)sig;
	write(2, "\b\b  \b\b", 6);
}

void	ctrl_d_exit(t_args *args, int i, char *rline)
{
	char	*temp;

	if (i == 0 && *rline == '\0' && line == NULL)
	{
		write(1, "\n", 1);
		free_strarr(args->env);
		if (rline)
			free(rline);
		if (line)
			free(line);
		exit(0);
	}
	if (line == NULL)
		line = rline;
	else
	{
		temp = line;
		line = ft_strjoin(line, rline);
		free(temp);
		free(rline);
	}
}

int		prompt(t_args *args)
{
	int		i;
	char	*rline;

	while (1)
	{
		if (line == NULL)
			write(1, "> ", 2);
		rline = NULL;
		i = get_next_line(0, &rline);
		ctrl_d_exit(args, i, rline);
		if (i == 0)
			continue ;
		if ((*line) != '\0')
		{
			if (!(parser(args, line)))
				exit(0);
		}
		free(line);
		line = NULL;
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_args	args;

	(void)argc;
	(void)argv;
	exit_status = 0;
	args.temp_fd_0 = dup(0);
	args.temp_fd_1 = dup(1);
	if (!(args.env = ft_strarrdup(envp)))
		return (0);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	line = NULL;
	prompt(&args);
}
