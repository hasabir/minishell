/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:33:39 by namine            #+#    #+#             */
/*   Updated: 2022/11/14 16:42:17 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	it_exists(t_ev *list, char *str)
{
	while (list)
	{
		if (!ft_strcmp(str, list->env_var))
			return (1);
		list = list->next;
	}
	return (0);
}

void	print_export(t_list *list_command, t_param *param)
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
	g_global.exit_status = 0;
}

void	check_possibilities(t_param *param, char **ptr)
{
	if (ptr[1])
	{
		if (!it_exists(param->env, ptr[0]))
			add_node(&param->env, ptr);
		if (!it_exists(param->export, ptr[0]))
			add_node(&param->export, ptr);
		else
		{
			free_env_var_and_replace(param->env, ptr[0], ptr[1]);
			free_env_var_and_replace(param->export, ptr[0], ptr[1]);
		}
	}
	if (ptr[1] == NULL && !it_exists(param->export, ptr[0]))
		add_node(&param->export, ptr);
}

void	add_to_export_env(t_list *list_command, t_param *param)
{
	int		arg_index;
	char	**ptr;

	arg_index = 0;
	while (list_command->data->arguments[arg_index])
	{
		ptr = ft_split_customized(list_command->data->arguments[arg_index]);
		if (!check_argument_name(ptr[0]))
			ft_exit_status(list_command, "not a valid identifier",
				list_command->data->arguments[arg_index], 1);
		else
			check_possibilities(param, ptr);
		arg_index++;
		ft_free(ptr);
	}
}

void	ft_export(t_list *list_command, t_param *param)
{
	if (list_command->data->arguments == NULL)
		print_export(list_command, param);
	else
		add_to_export_env(list_command, param);
}
