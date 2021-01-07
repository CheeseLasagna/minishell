/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 22:39:52 by enoelia           #+#    #+#             */
/*   Updated: 2020/05/25 13:33:19 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	a;

	if (!ft_strlen(little))
		return ((char*)big);
	i = 0;
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			a = 0;
			while (big[i + a] && little[a] &&
					big[i + a] == little[a] && a + i < len)
				a++;
			if (!little[a])
				return ((char*)big + i);
		}
		i++;
	}
	return (NULL);
}
