/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:32:54 by enoelia           #+#    #+#             */
/*   Updated: 2020/05/22 17:29:58 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charinset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1len;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	s1len = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_charinset(s1[i], set))
		i++;
	while (s1[s1len - 1] && ft_charinset(s1[s1len - 1], set))
		s1len--;
	if (s1len < i)
		i = s1len;
	if (!(result = malloc(sizeof(char) * (s1len - i + 1))))
		return (NULL);
	ft_strlcpy(result, s1 + i, s1len - i + 1);
	return (result);
}
