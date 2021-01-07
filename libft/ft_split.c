/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:49:19 by enoelia           #+#    #+#             */
/*   Updated: 2020/05/27 15:53:44 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countparts(const char *s, char c)
{
	size_t	parts;
	size_t	i;

	parts = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (i != 0 && s[i - 1] == c && s[i] != c))
			parts++;
		i++;
	}
	return (parts);
}

static int	ft_partlen(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	ft_free(char **parts, size_t partscounter)
{
	size_t i;

	i = 0;
	while (i < partscounter)
	{
		free(parts[partscounter]);
		partscounter--;
	}
	free(parts);
}

static char	**ft_fillparts(const char *s, char c, size_t count)
{
	size_t	i;
	size_t	len;
	size_t	partscounter;
	char	**parts;

	if (!(parts = (char**)malloc(sizeof(char*) * count + 1)))
		return (NULL);
	i = 0;
	partscounter = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (i != 0 && s[i - 1] == c && s[i] != c))
		{
			len = ft_partlen(s + i, c) + 1;
			if (!(parts[partscounter] = (char*)malloc(sizeof(char) * len)))
			{
				ft_free(parts, partscounter);
				return (NULL);
			}
			ft_strlcpy(parts[partscounter], s + i, len);
			partscounter++;
		}
		i++;
	}
	return (parts);
}

char		**ft_split(const char *s, char c)
{
	size_t	count;
	char	**parts;

	if (!s)
		return (NULL);
	count = ft_countparts(s, c);
	if (!(parts = ft_fillparts(s, c, count)))
		return (NULL);
	parts[count] = NULL;
	return (parts);
}
