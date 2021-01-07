/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:13:19 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/07 14:13:23 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**change_env(char **env, char *oldpwd, char *pwd)
{
	char *key;
	char *exp;
	char *args[3];

	key = "OLDPWD=";
	args[0] = "export";
	args[2] = NULL;
	key = ft_strjoin(key, oldpwd);
	if (key == NULL)
		return (env);
	exp = key;
	args[1] = exp;
	env = export(args, env);
	free(key);
	key = "PWD=";
	key = ft_strjoin(key, pwd);
	if (key == NULL)
		return (env);
	exp = key;
	args[1] = exp;
	env = export(args, env);
	free(key);
	return (env);
}

int		check_cd_args(char **args)
{
	if (*args == NULL)
	{
		return (1);
	}
	if (*(args + 1) != NULL)
	{
		write(1, "bash: cd: too many arguments\n", 29);
		exit_status = 1;
		return (1);
	}
	return (0);
}

char	*get_directory(void)
{
	int		size;
	char	*path;

	size = 100;
	path = (char*)malloc(sizeof(char) * size);
	if (path == NULL)
		return (NULL);
	while (getcwd(path, size) == NULL)
	{
		free(path);
		size = size + 50;
		path = (char*)malloc(sizeof(char) * size);
		if (path == NULL)
			return (NULL);
	}
	return (path);
}

int		check_path(char **args)
{
	char *err;

	if (chdir(*args) == -1)
	{
		err = strerror(errno);
		write(1, "bash: cd: ", 10);
		write(1, *args, ft_strlen(*args));
		write(1, ": ", 2);
		write(1, err, ft_strlen(err));
		write(1, "\n", 1);
		exit_status = 1;
		return (1);
	}
	return (0);
}

char	**cd(char **args, char **env)
{
	char *s;
	char *test;

	args++;
	if (check_cd_args(args) == 1)
		return (env);
	test = get_directory();
	if (test == NULL)
		return (env);
	if (check_path(args) == 1)
	{
		free(test);
		return (env);
	}
	s = get_directory();
	if (s == NULL)
	{
		free(test);
		return (env);
	}
	env = change_env(env, test, s);
	free(test);
	free(s);
	return (env);
}
