/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 19:17:15 by enoelia           #+#    #+#             */
/*   Updated: 2020/11/28 11:33:15 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*mpointer;

	mpointer = malloc(nmemb * size);
	if (!mpointer)
		return (NULL);
	ft_memset(mpointer, 0, nmemb * size);
	return (mpointer);
}
