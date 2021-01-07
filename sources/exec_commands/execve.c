/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:10:23 by tlavelle          #+#    #+#             */
/*   Updated: 2021/01/07 15:10:25 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_path_variable(char **args, char **env, char **path)
{
	char *temp;

	temp = "PATH=";
	while (*env != NULL)
	{
		if ((ft_strncmp(temp, *env, 5)) == 0)
		{
			*path = *env;
			return (0);
		}
		env++;
	}
	ft_putstr(*args);
	ft_putstr(": command not found\n");
	return (1);
}

int		path_len(char *path)
{
	int len;

	len = 0;
	while (*path != ':' && *path != '\0')
	{
		path++;
		len++;
	}
	return (len);
}

char	*get_command_path(char **temp)
{
	char	*temp_ptr;
	char	*path;
	int		len;

	len = path_len(*temp);
	path = (char*)malloc(sizeof(char) * (len + 2));
	temp_ptr = path;
	while (len != 0)
	{
		*temp_ptr = **temp;
		temp_ptr++;
		(*temp)++;
		len--;
	}
	*temp_ptr = '/';
	temp_ptr++;
	*temp_ptr = '\0';
	if (**temp == ':')
		(*temp)++;
	return (path);
}

int		path_included(char **args, char **env)
{
	int res;

	res = 0;
	if (**args == '.' || **args == '/')
		res = execve(*args, args, env);
	if ((ft_strchr(*args, '/')) != NULL)
		res = execve(*args, args, env);
	if (res == -1)
	{
		ft_putstr(*args);
		ft_putstr(": No such file or directory\n");
	}
	return (res);
}

int		try_execve(char **args, char **env)
{
	char *temp;
	char *path;
	char *leak;

	if ((path_included(args, env)) != 0)
		return (-1);
	if ((find_path_variable(args, env, &temp)) == 1)
		return (-1);
	while (*temp != '=')
		temp++;
	temp++;
	while (*temp != '\0')
	{
		path = get_command_path(&temp);
		leak = path;
		path = ft_strjoin(path, *args);
		execve(path, args, env);
		free(path);
		free(leak);
	}
	ft_putstr(*args);
	ft_putstr(": command not found\n");
	return (-1);
}
