/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:52:08 by namine            #+#    #+#             */
/*   Updated: 2022/10/27 22:31:42 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_linked_list **lst, void (*del)(void*))
{
	t_linked_list	*current;
	t_linked_list	*next_node;

	if (!lst || !del)
		return ;
	current = *lst;
	next_node = *lst;
	while (current)
	{
		next_node = next_node->next;
		ft_lstdelone(current, del);
		current = next_node;
	}
	*lst = NULL;
}
