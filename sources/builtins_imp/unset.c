/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:59:36 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/07 14:59:43 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_double_array_unset(char *old, char **env, int oldlen)
{
	char	**env1;
	char	**new;
	char	**new1;
	int		len;

	len = ft_strarrlen(env);
	if (!(new = (char**)malloc(sizeof(char*) * len)))
		return (env);
	env1 = env;
	new1 = new;
	while (*env1 != NULL)
	{
		if ((ft_strncmp(old, *env1, oldlen)) != 0)
		{
			*new1 = ft_strdup(*env1);
			new1++;
			env1++;
		}
		else
			env1++;
	}
	*new1 = NULL;
	ft_strarrclear(&env);
	return (new);
}

char	**find_and_remove(char *arg, char **env)
{
	int		len;
	char	**env1;
	int		x;

	env1 = env;
	while (*env1 != NULL)
	{
		len = keylen(*env1);
		x = ft_strncmp(arg, *env1, len);
		if (!x)
		{
			env = new_double_array_unset(*env1, env, len);
			return (env);
		}
		env1++;
	}
	return (env);
}

int		check_args_unset(char *arg)
{
	char *c;

	c = arg;
	while (*c != '\0')
	{
		if (*c < 48 || (*c > 57 && *c < 65) ||
		(*c > 90 && *c < 95) || *c == 96 || *c > 122)
		{
			write(1, "bash: unset: '", 14);
			write(1, arg, ft_strlen(arg));
			write(1, "': not a valid identifier\n", 26);
			exit_status = 1;
			return (1);
		}
		c++;
	}
	return (0);
}

char	**unset(char **args, char **env)
{
	args++;
	while (*args != NULL)
	{
		if (!(check_args_unset(*args)))
			env = find_and_remove(*args, env);
		args++;
	}
	return (env);
}
