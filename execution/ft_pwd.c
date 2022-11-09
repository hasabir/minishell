/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 04:49:43 by namine            #+#    #+#             */
/*   Updated: 2022/11/09 07:29:03 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void    ft_pwd(t_list *list_command, t_param *param)
{
    char buf[1024];
    char *pwd;
    t_ev *tmp;
    
    pwd = getcwd(buf, 1024);
    if (pwd)
    {
        ft_putstr_fd(pwd, list_command->data->output_file);
        ft_putstr_fd("\n", list_command->data->output_file);
    }
    else
    {
        tmp = param->env;
        while (tmp)
        {
            if (!ft_strcmp("PWD", tmp->env_var))
            {
                ft_putstr_fd(tmp->value, list_command->data->output_file);
                ft_putstr_fd("\n", list_command->data->output_file);
            }
            tmp = tmp->next;
        }
    }
}
