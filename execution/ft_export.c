/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:33:39 by namine            #+#    #+#             */
/*   Updated: 2022/11/09 03:30:57 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char **ft_split_customized(char *str)
{
	char	**ptr;
	int		len;
	int		i;
	
	ptr = malloc(sizeof(char *) * 3);
	i = -1;
	len = 0;
	while (str[++i] && str[i] != '=')
		len++;
	ptr[0] = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
		ptr[0][i++] = *str++;
	ptr[0][i] = '\0';
	ptr[1] = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (*str == '=')
		str++;
	else
	{
		ptr[1] = NULL;
		return (ptr);
	}
	i = 0;
	while (*str)
		ptr[1][i++] = *str++;
	ptr[1][i] = '\0';
	ptr[2] = NULL;
	return (ptr);
}

void add_node(t_ev *list, char **ptr)
{
	t_ev	*tmp;

	if (!list)
	{
		list = malloc(sizeof(t_ev));
		list->env_var = ft_strdup(ptr[0]);
		list->value = ft_strdup(ptr[1]);
		list->next = NULL;
		return ;
	}
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_ev));
	tmp = tmp->next;
	tmp->env_var = ft_strdup(ptr[0]);
	tmp->value = ft_strdup(ptr[1]);
	tmp->next = NULL;
}

int it_exists(t_ev *list, char *str)
{
	while (list)
	{
		if (!ft_strcmp((str), list->env_var))
			return (1);
		list = list->next;
	}
	return (0);
}

void ft_replace(t_ev *list, char **ptr)
{
	while (list)
	{
		if (!ft_strcmp((ptr[0]), list->env_var))
		{
			free(list->value);
			list->value = ft_strdup(ptr[1]);
			break ;
		}
		list = list->next;
	}
}

void	ft_export(t_list *list_command, t_param *param)
{
	char	**ptr;
	t_ev	*tmp;
    int		i;
	
	if (list_command->data->arguments == NULL)
    {
		tmp = param->export;
		while (tmp)
		{
			ft_putstr_fd("declare -x ", list_command->data->output_file);
			ft_putstr_fd(tmp->env_var, list_command->data->output_file);
			ft_putstr_fd("=\"", list_command->data->output_file);
			ft_putstr_fd(tmp->value, list_command->data->output_file);
			ft_putstr_fd("\"\n", list_command->data->output_file);
			tmp = tmp->next;
		}
    }
	else
	{
		i = 0;
		while (list_command->data->arguments[i])
		{
			ptr = ft_split_customized(list_command->data->arguments[i]);
			if (ptr[1])
			{
				if (!it_exists(param->env, ptr[0]))
					add_node(param->env, ptr);
				if (!it_exists(param->export, ptr[0]))
					add_node(param->export, ptr);
				else
				{
					ft_replace(param->env, ptr);
					ft_replace(param->export, ptr);
				}
			}
			else if (ptr[1] == NULL && !it_exists(param->export, ptr[0]))
			{
				add_node(param->export, ptr);
			}
			ft_free(ptr);
			i++;
		}
	}
}
// chekc name >> first chart >> aplaa le reste alphanum
