/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_(*lst)last_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:33:25 by namine            #+#    #+#             */
/*   Updated: 2022/10/23 13:20:57 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_list_last(t_list **lst, t_list *new)
{
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	(*lst)->next = new;
	(*lst) = new;
}
