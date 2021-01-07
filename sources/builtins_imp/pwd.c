/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:12:52 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/07 14:12:55 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*s;
	int		size;

	size = 100;
	s = (char*)malloc(sizeof(char) * size);
	if (s == NULL)
		return ;
	while (getcwd(s, size) == NULL)
	{
		free(s);
		size = size + 50;
		s = (char*)malloc(sizeof(char) * size);
		if (s == NULL)
			return ;
	}
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
	free(s);
}
