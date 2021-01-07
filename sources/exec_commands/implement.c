/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:09:15 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/07 15:09:17 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**implement(char **args, char **env, int imp)
{
	int status;

	status = exit_status;
	exit_status = 0;
	if (imp == 1)
		echo(args);
	else if (imp == 2)
		env = cd(args, env);
	else if (imp == 3)
		pwd();
	else if (imp == 4)
		env = export(args, env);
	else if (imp == 5)
		env = unset(args, env);
	else if (imp == 6)
		envp(env);
	else
	{
		exit_status = status;
		my_exit(args, env);
	}
	return (env);
}
