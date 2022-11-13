/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:33:39 by namine            #+#    #+#             */
/*   Updated: 2022/11/12 20:12:25 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char **ft_split_customized(char *str) // a optimiser
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
	if (*str == '=')
		str++;
	else
	{
		ptr[1] = NULL;
		return (ptr);
	}
	ptr[1] = malloc(sizeof(char) * (ft_strlen(str) + 1));
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
		if (!ft_strcmp(str, list->env_var))
			return (1);
		list = list->next;
	}
	return (0);
}

void print_export(t_list *list_command, t_param *param)
{
	t_ev	*tmp;
	
	tmp = param->export;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", list_command->data->output_file);
		ft_putstr_fd(tmp->env_var, list_command->data->output_file);
		if (tmp->value)
			ft_putstr_fd("=\"", list_command->data->output_file);
		ft_putstr_fd(tmp->value, list_command->data->output_file);
		if (tmp->value)
			ft_putstr_fd("\"", list_command->data->output_file);
		ft_putstr_fd("\n", list_command->data->output_file);
		tmp = tmp->next;
	}
}

void check_possibilities(t_param *param, char	**ptr)
{
	if (ptr[1])
	{
		if (!it_exists(param->env, ptr[0]))
			add_node(param->env, ptr);
		if (!it_exists(param->export, ptr[0]))
			add_node(param->export, ptr);
		else
		{
			free_env_var_and_replace(param->env, ptr[0], ptr[1]);
			free_env_var_and_replace(param->export, ptr[0], ptr[1]);
		}
	}
	if (ptr[1] == NULL && !it_exists(param->export, ptr[0]))
		add_node(param->export, ptr);
}

void add_to_export(t_list *list_command, t_param *param)
{
    int		arg_index;
	char	**ptr;
	
	arg_index = 0;
	while (list_command->data->arguments[arg_index])
	{
		ptr = ft_split_customized(list_command->data->arguments[arg_index]);
		if (!check_argument_name(ptr[0]))
		{
			error_msg(list_command, list_command->data->cmd, "not a valid identifier\n", list_command->data->arguments[arg_index]);
			arg_index++;
			ft_free(ptr);
			continue;
		}
		check_possibilities(param, ptr);
		ft_free(ptr);
		arg_index++;
	}
}

void	ft_export(t_list *list_command, t_param *param)
{
	if (list_command->data->arguments == NULL)
		print_export(list_command, param);
	else
		add_to_export(list_command, param);
}
