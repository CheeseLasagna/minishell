/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 18:52:59 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/12 19:58:24 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return (0);
	new->next = *lst;
	*lst = new;
	return (1);
}
