/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:31:12 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/07 02:58:45 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		add_int_to_intarr(int value, int **intarrp, int intarr_num)
{
	int i;
	int	*tmp;

	tmp = *intarrp;
	if (!(*intarrp = ft_calloc(sizeof(int), (intarr_num + 2))))
		return (0);
	i = 0;
	while (tmp[i])
	{
		(*intarrp)[i] = tmp[i];
		i++;
	}
	(*intarrp)[i] = value;
	if (tmp)
		free(tmp);
	return (1);
}

int		is_str_empty(char *str)
{
	str++;
	while ((*(str + 1)) == ' ')
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

int		parse_redirect_symbols(t_args *args, char ***strarr
									, int *strnum, char **str)
{
	int		status;

	if (!(*(args->argv)) && is_str_empty(*str))
	{
		ft_putstr("bash: syntax error near unexpected token `newline'\n");
		return (exit_status = 2);
	}
	while (!ft_strchr(FILE_SPEC_SYMBOLS, **str))
	{
		if (**str == '$')
			status = parse_env(args, strarr, strnum, str);
		else if (**str == '\'')
			status = add_signalquoted_str_to_str(&((*strarr)[*strnum]), str);
		else if (**str == '\"')
			status = add_doublequoted_str_to_str(args, strarr, strnum, str);
		else if (**str == '\\')
			status = replace_escape_symbol(&((*strarr)[*strnum]), str);
		else
			status = add_char_to_str(&((*strarr)[*strnum]), **str);
		if (!status)
			return (0);
		(*str)++;
	}
	(*str)--;
	return (1);
}

int		parse_redirect(t_args *args, char ***strarr, int *strnum, char **str)
{
	int status;

	status = 1;
	status = add_empty_str_in_strarr(strarr, strnum);
	if (**str == '>')
		args->write_to = 2;
	(*str)++;
	if (**str == '>')
	{
		(*str)++;
		status = add_int_to_intarr(2, &args->write_append, *strnum);
	}
	else
		status = add_int_to_intarr(1, &args->write_append, *strnum);
	if (!status)
		return (0);
	while (**str == ' ')
		(*str)++;
	return (parse_redirect_symbols(args, strarr, strnum, str));
}
