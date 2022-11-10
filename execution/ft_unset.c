/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:37:22 by namine            #+#    #+#             */
/*   Updated: 2022/11/10 02:06:51 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_node(t_ev *node)
{
	if(node->env_var)
		free(node->env_var);
	if (node->value)
		free(node->value);
	free(node);
}

void	remove_node(t_ev *list, t_ev *node)
{
	t_ev	*previous;
	t_ev	*current;

	current = list;
	previous = NULL;
	if (current == NULL || node == NULL)
		return ;
	int i = 0;
	while (current)
	{
		if(current == node)
		{
			if(current == list)
				list = list->next;
			if (previous != NULL)
				previous->next = current->next;
			free_node(current);
			break;
		}
		previous = current;
		current = current->next;
		i++;
	}
}

void	remove_node_by_index(t_ev *list, int index)
{
	t_ev	*current;
	int		i;

	i = 0;
	current = list;
	while (i < index && current)
	{
		current = current->next;
		i++;
	}
	remove_node(list, current);
}

int		get_index(t_ev *list, char *arg)
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
	return (index);
}	

void	ft_unset(t_list *list_command, t_param *param)
{
	int	arg_index;

	if (list_command->data->arguments)
	{
		arg_index = 0;
		while (list_command->data->arguments[arg_index])
		{
			if (!check_argument(list_command->data->arguments[arg_index]))
				error_msg(list_command, ": not a valid identifier\n", arg_index);
			else
			{
				remove_node_by_index(param->env, get_index(param->env, list_command->data->arguments[arg_index]));
				remove_node_by_index(param->export, get_index(param->export, list_command->data->arguments[arg_index]));
			}
			arg_index++;
		}
	}
}
