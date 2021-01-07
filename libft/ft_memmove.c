/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 15:09:08 by enoelia           #+#    #+#             */
/*   Updated: 2020/05/25 19:50:30 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*charsrc;
	unsigned char	*chardest;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	charsrc = (unsigned char*)src;
	chardest = (unsigned char*)dest;
	while (n > 0)
	{
		n--;
		chardest[n] = charsrc[n];
	}
	return (chardest);
}
