/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:37:16 by namine            #+#    #+#             */
/*   Updated: 2022/11/14 17:17:47 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_env(t_list *list_command, t_param *param)
{
	t_ev	*tmp;

	if (list_command->data->arguments)
		ft_exit_status(list_command, "No such file or directory",
			list_command->data->arguments[0], 127);
	else if (list_command->data->options)
		ft_exit_status(list_command, "too many arguments",
			list_command->data->options[0], 1);
	else
	{
		tmp = param->env;
		while (tmp)
		{
			ft_putstr_fd(tmp->env_var, list_command->data->output_file);
			ft_putstr_fd("=", list_command->data->output_file);
			ft_putstr_fd(tmp->value, list_command->data->output_file);
			ft_putstr_fd("\n", list_command->data->output_file);
			tmp = tmp->next;
		}
		g_global.exit_status = 0;
	}
}
