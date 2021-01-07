/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 12:57:55 by enoelia           #+#    #+#             */
/*   Updated: 2020/05/27 12:53:05 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newelem;

	if (!lst || !f || !del)
		return (NULL);
	if (!(newelem = ft_lstnew(f(lst->content))))
	{
		return (NULL);
	}
	newlst = newelem;
	lst = lst->next;
	while (lst)
	{
		if (!(newelem = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&newlst, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&newlst, newelem);
	}
	return (newlst);
}
