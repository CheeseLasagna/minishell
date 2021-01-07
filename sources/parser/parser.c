/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:57:20 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/07 03:37:32 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		clean_last_whitespace(t_args *args)
{
	if (!(*(args->argv)) && !(*(args->inp_files))
		&& !(*(args->red_files)))
		return (0);
	if (!(*(args->argv)))
		return (1);
	if (args->argv[args->argc][0] == '\0')
		remove_last_str_in_strarr(&(args->argv), &(args->argc));
	if (!(add_strarr_to_strarr(&args->argv, &(args->inp_files))))
		return (0);
	return (1);
}

int		parse_spec_symbol(t_args *args, char **str)
{
	int status;

	status = 1;
	if (**str == ';')
		status = check_semicolon(args, str);
	else if (**str == '$')
		status = parse_env(args, &(args->argv), &(args->argc), str);
	else if (**str == '\'')
		status = add_signalquoted_str_to_str(&(args->argv[args->argc]), str);
	else if (**str == '\"')
		status = add_doublequoted_str_to_str(args, &(args->argv)
											, &(args->argc), str);
	else if (**str == ' ')
		status = parse_spaces(&(args->argv), &(args->argc), str);
	else if (**str == '\\')
		status = replace_escape_symbol(&(args->argv[args->argc]), str);
	else if (**str == '|')
		status = parse_pipe(args);
	else if (**str == '<')
		status = parse_redirect(args, &(args->inp_files)
								, &(args->inp_count), str);
	else if (**str == '>')
		status = parse_redirect(args, &(args->red_files)
								, &(args->red_count), str);
	return (status);
}

int		parser_str(t_args *args, char *str)
{
	int		status;

	status = 1;
	while (*str)
	{
		if (ft_strchr(SPEC_SYMBOLS, *str))
			status = parse_spec_symbol(args, &str);
		else
			status = add_char_to_str(&(args->argv[args->argc]), *str);
		if (status == 2)
		{
			free_arg_struct(args);
			return (1);
		}
		if (!status)
			return (0);
		str++;
	}
	return (2);
}

int		parser(t_args *args, char *input_str)
{
	char	*str;
	int		status;

	if (!init_arg_struct(args))
		return (0);
	str = input_str;
	status = parser_str(args, str);
	if (status != 2)
		return (status);
	if (!(clean_last_whitespace(args)))
		return (1);
	exec_command(args);
	free_arg_struct(args);
	return (1);
}
