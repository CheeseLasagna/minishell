/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:12:34 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/07 14:12:43 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *str)
{
	if (!str)
		return ;
	write(1, str, ft_strlen(str));
}

void	echo(char **args)
{
	int flag;

	flag = 0;
	args++;
	if (*args == NULL)
		flag = 1;
	else if (ft_strncmp(*args, "-n", 3) == 0)
	{
		while (*args != NULL && ft_strncmp(*args, "-n", 3) == 0)
			args++;
	}
	else
		flag = 1;
	while (*args != NULL)
	{
		ft_putstr(*args);
		args++;
		if (*args != NULL)
			write(1, " ", 1);
	}
	if (flag)
		write(1, "\n", 1);
}
