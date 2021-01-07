/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarrs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 21:47:38 by enoelia           #+#    #+#             */
/*   Updated: 2021/01/01 22:13:40 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strarrprint(char **strarr)
{
	int i;

	i = 0;
	while (strarr && strarr[i])
	{
		ft_putstr(strarr[i]);
		ft_putstr("\n");
		i++;
	}
	return (i);
}

int		ft_strarrlen(char **strarr)
{
	int i;

	i = 0;
	while (strarr && strarr[i])
		i++;
	return (i);
}

int		ft_strarrclear(char ***strarrp)
{
	int i;

	i = 0;
	while (strarrp && *strarrp && (*strarrp)[i])
	{
		free((*strarrp)[i]);
		(*strarrp)[i] = NULL;
		i++;
	}
	if (strarrp && *strarrp)
	{
		free(*strarrp);
		*strarrp = NULL;
	}
	return (0);
}

char	**ft_strarrdup(char **src)
{
	int		i;
	int		src_len;
	char	**dest;

	src_len = ft_strarrlen(src);
	if (!(dest = ft_calloc(sizeof(char *), (src_len + 1))))
		return (NULL);
	i = 0;
	while (src && src[i])
	{
		if (!(dest[i] = ft_strdup(src[i])))
		{
			ft_strarrclear(&dest);
			return (NULL);
		}
		i++;
	}
	return (dest);
}

int		add_empty_str_in_strarr(char ***strarr, int *strnum)
{
	char	**tmp;
	int		i;

	if (!(*strarr)[0])
		return (1);
	tmp = (*strarr);
	*strnum += 1;
	if (!(*strarr = ft_calloc(sizeof(char *), (*strnum) + 2)))
		return (0);
	i = 0;
	while (i < *strnum)
	{
		(*strarr)[i] = tmp[i];
		i++;
	}
	if (!((*strarr)[*strnum] = ft_strdup("")))
		return (0);
	free(tmp);
	return (1);
}
