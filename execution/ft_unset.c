/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:37:22 by namine            #+#    #+#             */
/*   Updated: 2022/11/15 03:15:25 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_node(t_ev *node)
{
	if (node->env_var)
		free(node->env_var);
	if (node->value)
		free(node->value);
	free(node);
}

void	remove_node(t_ev *list, t_ev *node)
{
	t_ev	*previous;
	t_ev	*current;
	int		i;

	current = list;
	previous = NULL;
	if (current == NULL || node == NULL)
		return ;
	i = 0;
	while (current)
	{
		if (current == node)
		{
			if (current == list)
				list = list->next;
			if (previous != NULL)
				previous->next = current->next;
			free_node(current);
			break ;
		}
		previous = current;
		current = current->next;
		i++;
	}
}

void	remove_node_by_index(t_ev **list, int index, t_param *param)
{
	t_ev	*current;
	int		i;

	i = 0;
	current = *list;
	(void)param;
	if (index == 0)
	{
		*list = (*list)->next;
		free_node(current);
	}
	else
	{
		while (i < index && current)
		{
			current = current->next;
			i++;
		}
		remove_node(*list, current);
	}
}

int	id(t_ev *list, char *arg)
{
	t_ev	*tmp;
	int		index;

	tmp = list;
	index = 0;
	while (tmp)
	{
		if (!strcmp(arg, tmp->env_var))
			return (index);
		index++;
		tmp = tmp->next;
	}
	return (-1);
}	

void	ft_unset(t_list *list_command, t_param *param)
{
	int	arg_index;
	int	i;

	g_global.exit_status = 0;
	if (list_command->data->arguments)
	{
		arg_index = 0;
		while (list_command->data->arguments[arg_index])
		{
			if (!check_argument_name(list_command->data->arguments[arg_index]))
				ft_exit_status(list_command, "not a valid identifier",
					list_command->data->arguments[arg_index], 1);
			else
			{
				i = id(param->export, list_command->data->arguments[arg_index]);
				if (i != -1)
					remove_node_by_index(&(param->export), i, param);
				i = id(param->env, list_command->data->arguments[arg_index]);
				if (i != -1)
					remove_node_by_index(&(param->env), i, param);
			}
			arg_index++;
		}
	}
}
