/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:03:54 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/07 15:03:57 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		keylen(char *key)
{
	int len;

	len = 0;
	while (*key != '=' && *key != '\0')
	{
		len++;
		key++;
	}
	return (len);
}

void	export_arg_error(char *arg)
{
	write(1, "bash: export: '", 15);
	write(1, arg, ft_strlen(arg));
	write(1, "': not a valid identifier\n", 26);
}

int		check_args_export(char *arg)
{
	char *c;

	if (!((*arg > 64 && *arg < 91) || (*arg > 96 && *arg < 123) || *arg == 95))
	{
		export_arg_error(arg);
		exit_status = 1;
		return (1);
	}
	c = arg;
	while (*c != '\0')
	{
		if (*c < 32 || (*c > 32 && *c < 36) || (*c > 36 && *c < 47) ||
		(*c > 57 && *c < 61) || (*c > 61 && *c < 65) || (*c > 90 && *c < 92)
		|| (*c > 92 && *c < 95) || *c == 96 || *c > 122)
		{
			export_arg_error(arg);
			exit_status = 1;
			return (1);
		}
		c++;
	}
	return (0);
}
