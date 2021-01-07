/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tlst_to_chararr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:04:02 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/14 19:52:10 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tlst_to_chararr(t_list *tlst)
{
	char	**arr;
	int		i;
	int		size;

	size = ft_lstsize(tlst);
	if (!(arr = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (tlst)
	{
		arr[i] = ft_strdup(tlst->content);
		tlst = tlst->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
