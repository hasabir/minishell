/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:37:16 by namine            #+#    #+#             */
/*   Updated: 2022/11/05 04:38:49 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void    ft_env(t_list *list_command, t_param *param)
{
    t_ev *tmp;

    tmp = param->env;
    while (tmp)
    {
        ft_putstr_fd(tmp->env_var, list_command->data->output_file);
        ft_putstr_fd("=", list_command->data->output_file);
        ft_putstr_fd(tmp->value, list_command->data->output_file);
        ft_putstr_fd("\n", list_command->data->output_file);
        tmp = tmp->next;
    }
}
