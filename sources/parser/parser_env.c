/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:31:50 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/06 20:20:56 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_env_value(t_args *args, char ***strarr
						, int *strnum, char **env_value)
{
	int		status;
	char	*tmp;

	status = 1;
	tmp = *env_value;
	while (**env_value != '\0')
	{
		if (**env_value == '\\')
		{
			if (*(*env_value + 1) == '\\' && *(*env_value + 1) == '$')
				env_value++;
			status = add_char_to_str(&((*strarr)[*strnum]), **env_value);
		}
		else if (**env_value == ' ')
			status = parse_spaces(strarr, strnum, env_value);
		else if (**env_value == '$')
			status = parse_env(args, strarr, strnum, env_value);
		else
			status = add_char_to_str(&((*strarr)[*strnum]), **env_value);
		if (!status)
			return (0);
		(*env_value)++;
	}
	free(tmp);
	return (1);
}

int		parse_env(t_args *args, char ***strarr, int *strnum, char **str)
{
	char	*env_name;
	char	*env_value;

	(*str)++;
	if (**str == '?')
	{
		return (((*strarr)[*strnum] = add_str_to_str((*strarr)[*strnum]
									, ft_itoa(exit_status))) ? 1 : 0);
	}
	if (!**str || ft_strchr(SPEC_SYMBOLS, **str))
	{
		(*str)--;
		return (add_char_to_str(&((*strarr)[*strnum]), '$'));
	}
	if (!(env_name = parse_env_name(str)))
		return (0);
	if (!(env_value = find_env_value(args, env_name, 0)))
		return (0);
	if (!(parse_env_value(args, strarr, strnum, &env_value)))
		return (0);
	free(env_name);
	return (1);
}

char	*find_env_value(t_args *args, char *env_name, int i)
{
	char	*varname_end;
	int		result_len;
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	while (result && args->env && args->env[i])
	{
		if ((varname_end = ft_strchr(args->env[i], '=')))
		{
			if (ft_strncmp(env_name, args->env[i], ft_strlen(env_name)) == 0)
			{
				result_len = ft_strlen(varname_end + 1);
				tmp = result;
				if (!(result = ft_calloc(1, result_len + 1)))
					return (NULL);
				free(tmp);
				ft_strlcpy(result, varname_end + 1, result_len + 1);
				break ;
			}
		}
		i++;
	}
	return (result);
}

char	*parse_env_name(char **str)
{
	char	*env_name;
	int		i;

	i = 0;
	env_name = ft_strdup("");
	while (env_name && **str)
	{
		if (i == 0 && ft_isdigit(**str))
			return (env_name);
		if (ft_isalnum(**str) || ((**str) == '_'))
			add_char_to_str(&env_name, **str);
		else
		{
			(*str)--;
			return (env_name);
		}
		(*str)++;
		i++;
	}
	(*str)--;
	return (env_name);
}
