/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 21:49:23 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/02 23:05:16 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_str_to_str(char *src1, char *src2)
{
	char	*result;
	int		src1_len;
	int		src2_len;

	if (!src2)
		return (NULL);
	src1_len = ft_strlen(src1);
	src2_len = ft_strlen(src2);
	if (!(result = ft_calloc(1, src1_len + src2_len + 1)))
		return (NULL);
	ft_strlcpy(result, src1, src1_len + 1);
	ft_strlcpy(result + src1_len, src2, src2_len + 1);
	if (src1)
		free(src1);
	free(src2);
	return (result);
}

int		add_char_to_str(char **strp, char symbol)
{
	char	*tmp;
	int		str_len;

	tmp = *strp;
	str_len = ft_strlen(*strp);
	if (!(*strp = malloc(str_len + 2)))
		return (0);
	(*strp)[str_len + 1] = '\0';
	ft_strlcpy(*strp, tmp, str_len + 1);
	(*strp)[str_len] = symbol;
	if (tmp)
		free(tmp);
	return (1);
}
