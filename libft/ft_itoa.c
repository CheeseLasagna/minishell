/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 17:11:52 by enoelia           #+#    #+#             */
/*   Updated: 2020/05/22 17:24:28 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n, int *isnegative)
{
	int		len;
	long	ln;

	ln = n;
	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		ln = -ln;
		*isnegative = 1;
	}
	while (ln > 0)
	{
		ln /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int		len;
	long	ln;
	int		isnegative;
	char	*str;

	isnegative = 0;
	len = ft_intlen(n, &isnegative);
	ln = n;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	if (ln < 0)
	{
		str[0] = '-';
		ln = -ln;
	}
	while (len >= isnegative)
	{
		str[len] = ln % 10 + '0';
		ln /= 10;
		len--;
	}
	return (str);
}
