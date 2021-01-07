/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 19:23:47 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/14 16:50:20 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst && *lst)
		ft_lstlast(*lst)->next = new;
	else if (lst)
		*lst = new;
	if (!new)
		return (0);
	return (1);
}
