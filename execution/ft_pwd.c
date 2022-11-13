/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 04:49:43 by namine            #+#    #+#             */
/*   Updated: 2022/11/12 21:56:19 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void    ft_pwd(t_list *list_command)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if (pwd)
    {
        ft_putstr_fd(pwd, list_command->data->output_file);
        ft_putstr_fd("\n", list_command->data->output_file);
    }
    else
        error_msg(list_command, list_command->data->cmd, "msse7tih\n", list_command->data->arguments[0]);
}
