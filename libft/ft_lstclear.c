/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 12:22:26 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/14 16:50:59 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmplst;
	t_list	*clearlst;

	if (!lst)
		return ;
	clearlst = *lst;
	while (clearlst)
	{
		tmplst = clearlst->next;
		ft_lstdelone(clearlst, del);
		clearlst = tmplst;
	}
	*lst = NULL;
}
