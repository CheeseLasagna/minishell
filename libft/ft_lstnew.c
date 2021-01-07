/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 18:46:22 by enoelia           #+#    #+#             */
/*   Updated: 2020/05/25 15:08:45 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *newelem;

	if (!(newelem = malloc(sizeof(t_list*))))
		return (NULL);
	newelem->next = NULL;
	newelem->content = content;
	return (newelem);
}
