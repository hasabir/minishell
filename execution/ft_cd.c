/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 04:49:41 by namine            #+#    #+#             */
/*   Updated: 2022/11/09 08:11:40 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char *home(t_param *param)
{
    t_ev *tmp;
    char *path;
    
    tmp = param->env;
    path = NULL;
    while (tmp)
    {
        if (!ft_strcmp("HOME", tmp->env_var))
            path = ft_strdup(tmp->value);
        tmp = tmp->next;
    }
    return (path);
}

void    ft_cd(t_list *list_command, t_param *param)
{
    int i;
    char *path;
    // char *tmp;
    
    if (!list_command->data->arguments)
    {
        path = home(param);
        chdir(path);
        free(path);   
    }
    else
    {
        // tmp = getcwd(NULL, 0);
        // crer un old path
        i = chdir(list_command->data->arguments[0]);
        if (i == -1)
            perror(" ");
        // printf old path
        t_ev *tmp = param->env;
        while (tmp)
        {
            if (!ft_strcmp("OLDPWD", tmp->env_var))
                printf("my old path not updated: %s\n", tmp->value);
            tmp = tmp->next;
        }
        // update_old_path();
        
    }
}
