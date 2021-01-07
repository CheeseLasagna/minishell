/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:07:00 by enoelia           #+#    #+#             */
/*   Updated: 2020/05/25 19:49:14 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*charsrc;
	unsigned char	*chardest;

	if (!dest && !src)
		return (NULL);
	if (!n)
		return (dest);
	charsrc = (unsigned char*)src;
	chardest = (unsigned char*)dest;
	i = 0;
	while (i < n)
	{
		chardest[i] = charsrc[i];
		i++;
	}
	return (dest);
}
