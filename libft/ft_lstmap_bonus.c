/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:57:18 by namine            #+#    #+#             */
/*   Updated: 2022/10/27 22:34:56 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_linked_list	*ft_lstmap(t_linked_list *lst,
	void *(*f)(void *), void (*del)(void *))
{
	t_linked_list	*pt;
	t_linked_list	*new_lst;

	if (!f)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		pt = ft_lstnew(f(lst->content));
		if (!pt)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, pt);
		lst = lst->next;
	}
	return (new_lst);
}
