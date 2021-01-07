/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 13:29:12 by enoelia           #+#    #+#             */
/*   Updated: 2020/05/25 12:50:04 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*charsrc;
	unsigned char	*chardest;
	unsigned char	charc;

	charsrc = (unsigned char *)src;
	chardest = (unsigned char *)dest;
	charc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		chardest[i] = charsrc[i];
		if (charsrc[i] == charc)
			return (&chardest[i + 1]);
		i++;
	}
	return (NULL);
}
