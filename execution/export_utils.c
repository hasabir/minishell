/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:30:30 by namine            #+#    #+#             */
/*   Updated: 2022/11/14 19:24:52 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**ft_split_customized(char *str)
{
	char	**ptr;
	int		len;
	int		i;

	ptr = malloc(sizeof(char *) * 3);
	if (!ptr)
		malloc_failed();
	i = -1;
	len = 0;
	while (str[++i] && str[i] != '=')
		len++;
	ptr[0] = ft_substr(str, 0, len);
	str += len;
	if (*str == '=')
		str++;
	else
	{
		ptr[1] = NULL;
		return (ptr);
	}
	ptr[1] = ft_strdup(str);
	ptr[2] = NULL;
	return (ptr);
}

void	add_node(t_ev **list, char **ptr)
{
	t_ev	*tmp;

	tmp = *list;
	if (!*list)
	{
		*list = malloc(sizeof(t_ev));
		if (!*list)
			malloc_failed();
		(*list)->env_var = ft_strdup(ptr[0]);
		(*list)->value = ft_strdup(ptr[1]);
		(*list)->next = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_ev));
	if (!tmp->next)
		malloc_failed();
	tmp = tmp->next;
	tmp->env_var = ft_strdup(ptr[0]);
	tmp->value = ft_strdup(ptr[1]);
	tmp->next = NULL;
}
