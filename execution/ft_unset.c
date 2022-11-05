/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:37:22 by namine            #+#    #+#             */
/*   Updated: 2022/11/05 10:33:46 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int check_argument(char *str)
{
    if (!ft_isalpha(*str))
        return (0);
	while (*str)
	{
		if (!ft_isalnum(*str))
			return (0);
		str++;
	}
	return (1);
}

void		free_node(t_ev *node)
{
	if(node->env_var)
		free(node->env_var);
	if (node->value)
		free(node->value);
	free(node);
}

int	ft_strcmp(const char	*s1, const char *s2)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*ss;

	s = (unsigned char *)s1;
	if (!s || !*s)
		return (-1);
	ss = (unsigned char *)s2;
	i = 0;
	while (s[i] && ss[i] && s[i] == ss[i])
		i++;
	return (s[i] - ss[i]);
}

void		remove_node(t_ev **head, t_ev *node)
{
	t_ev	*previous;
	t_ev	*current;

	current = *head;
	previous = NULL;
	if (current == NULL || node == NULL)
		return ;
	while (current)
	{
		if(current == node)
		{
			if(current == *head)
				(*head) = (*head)->next;
			if (previous != NULL)
				previous->next = current->next;
			// free_node(current);
			break;
		}
		previous = current;
		current = current->next;
	}
}

void		remove_node_by_index(t_ev **head, int index)
{
	t_ev	*current;
	int		i;

	i = 0;
	current = *head;
	while (i < index && current)
	{
		current = current->next;
		i++;
	}
	remove_node(head, current);
}

int get_index(t_ev *node, char *arg)
{
	int index;
	
	index = 0;
	while (node)
	{
		if (!strcmp(arg, node->env_var))
			return (index);
		index++;
		node = node->next;
	}
	return (index);
}	

void	check_args(t_list *list_command, t_param *param)
{
	// int	ret;
	int	i;
	
	t_ev *tmp = param->env;
	while (tmp)
	{
		printf("%s", tmp->env_var);
		printf("=");
		printf("%s", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
	i = 0;
	while (list_command->data->arguments[i])
	{
    	// ret = check_argument(list_command->data->arguments[i]);
		// if (ret == 0)
		// {
		// 	write(2, "Petit_shell: ", 14);
		// 	write(2, list_command->data->cmd, ft_strlen(list_command->data->cmd));
		// 	write(2, ": ", 2);
		// 	write(2, list_command->data->arguments[i], ft_strlen(list_command->data->arguments[i]));
		// 	write(2, ": not a valid identifier\n", 26);
		// }
		// else
		// {
			printf("index : > %d\n", get_index(param->env, list_command->data->arguments[i]));
			// remove_node_by_index(&param->env, get_index(param->env, list_command->data->arguments[i]));
		// }
		i++;
	}	
}

void    ft_unset(t_list *list_command, t_param *param)
{
	check_args(list_command, param);
}
