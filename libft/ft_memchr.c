/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:19:11 by enoelia           #+#    #+#             */
/*   Updated: 2020/05/25 13:20:56 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*chars;
	size_t			i;

	chars = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (chars[i] == (unsigned char)c)
			return (chars + i);
		i++;
	}
	return (NULL);
}
