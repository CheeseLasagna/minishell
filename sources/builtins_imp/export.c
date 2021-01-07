/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:59:53 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/07 14:59:55 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_double_array_export(char *arg, char **env, int len)
{
	char **new;
	char **new1;
	char **env1;

	env1 = env;
	if (!(new = (char **)malloc(sizeof(char *) * (len + 2))))
		return (env);
	new1 = new;
	while (*env1 != NULL)
	{
		if (!(*new1 = ft_strdup(*env1)))
		{
			ft_strarrclear(&new);
			return (env);
		}
		new1++;
		env1++;
	}
	*new1 = ft_strdup(arg);
	new1++;
	*new1 = NULL;
	ft_strarrclear(&env);
	return (new);
}

char	**add_to_env_list(char *arg, char **env)
{
	char	**env1;
	char	*temp;
	int		len_res;

	env1 = env;
	while (*env1 != NULL)
	{
		len_res = keylen(arg);
		len_res = ft_strncmp(arg, *env1, len_res + 1);
		if (!len_res)
		{
			temp = *env1;
			if (!(*env1 = ft_strdup(arg)))
			{
				*env1 = temp;
				return (env);
			}
			free(temp);
			return (env);
		}
		env1++;
	}
	len_res = ft_strarrlen(env);
	env = new_double_array_export(arg, env, len_res);
	return (env);
}

void	print_element_export(char *elem)
{
	char	*s;
	int		len;

	len = keylen(elem);
	s = ft_strchr(elem, '=');
	if (s == NULL)
	{
		s = ft_strchr(elem, '\0');
		write(1, "declare -x ", 11);
		write(1, elem, len);
		write(1, "\n", 1);
		return ;
	}
	else
		s++;
	write(1, "declare -x ", 11);
	write(1, elem, len + 1);
	write(1, "\"", 1);
	write(1, s, ft_strlen(s));
	write(1, "\"", 1);
	write(1, "\n", 1);
}

char	**export2(char **args, char **env)
{
	while (*args != NULL)
	{
		if (!(check_args_export(*args)))
			env = add_to_env_list(*args, env);
		args++;
	}
	return (env);
}

char	**export(char **args, char **env)
{
	char **env1;

	env1 = env;
	args++;
	if (*args == NULL)
	{
		while (*env1 != NULL)
		{
			print_element_export(*env1);
			env1++;
		}
	}
	else
		env = export2(args, env);
	return (env);
}
