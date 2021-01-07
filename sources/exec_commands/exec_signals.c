/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:08:58 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/07 15:09:00 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_skip(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	exit_status = 130;
}

void	sigquit_skip(int signum)
{
	(void)signum;
	ft_putstr("Quit (core dumped)\n");
	exit_status = 131;
}

void	sigint_child(int signum)
{
	(void)signum;
	exit(130);
}

void	sigquit_child(int signum)
{
	(void)signum;
	exit(131);
}
