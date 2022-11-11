/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 04:49:41 by namine            #+#    #+#             */
/*   Updated: 2022/11/11 05:31:56 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char *home(t_param *param)
{
    t_ev *tmp;
    
    tmp = param->env;
    while (tmp)
    {
        if (!ft_strcmp("HOME", tmp->env_var))
            return(ft_strdup(tmp->value));
        tmp = tmp->next;
    }
    return (NULL);
}

void    ft_cd(t_list *list_command, t_param *param)
{
    char *path;
    
    if (!list_command->data->arguments)
    {
        path = home(param);
        if (!path)
            error_msg(list_command, list_command->data->cmd, "HOME not set\n", 0);
        else
        {
            chdir(path);
            free(path);
        }
    }
    else
    {
        // // tmp = getcwd(NULL, 0);
        // // crer un old path
        // i = chdir(list_command->data->arguments[0]);
        // if (i == -1)
        //     perror(" ");
        // // printf old path
        // t_ev *tmp = param->env;
        // while (tmp)
        // {
        //     if (!ft_strcmp("OLDPWD", tmp->env_var))
        //         printf("my old path not updated: %s\n", tmp->value);
        //     tmp = tmp->next;
        // }
        // // update_old_path();
        
        
    }
}
