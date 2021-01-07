/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:26:39 by enoelia           #+#    #+#             */
/*   Updated: 2020/12/17 00:23:12 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	str[500];//find out size of shell command line limit
	char	**our_envp;
	int		readen;

	(void)argc;
	(void)argv;
	if (!(our_envp = ft_strarrdup(envp)))
		return (0);//malloc error
	while(1)
	{
		write(1, "> ", 2);
		readen = read(1, str, 500);
		str[readen - 1] = '\0';
		parser(str, our_envp);
	}
	ft_strarrclear(&our_envp);//add to signal_handler
	return (0);
}