/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 04:49:41 by namine            #+#    #+#             */
/*   Updated: 2022/11/12 17:10:00 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

void cd_with_arg(t_list *list_command, t_param *param)
{
    char *oldpwd;
    t_ev *tmp;
    char *pwd;
    
    oldpwd = getcwd(NULL, 0);
    tmp = param->env;
    while (tmp)
    {
        if (!ft_strcmp("OLDPWD", tmp->env_var))
        {
            free(tmp->value);
            tmp->value = ft_strdup(oldpwd);
            break;
        }
        tmp = tmp->next;
    }
    free(oldpwd);
    if (chdir(list_command->data->arguments[0]) == -1)
        error_msg(list_command, list_command->data->cmd, strerror(errno), list_command->data->arguments[0]);
    pwd = getcwd(NULL, 0);
    tmp = param->env;
    while (tmp)
    {
        if (!ft_strcmp("PWD", tmp->env_var))
        {
            free(tmp->value);
            tmp->value = ft_strdup(pwd);
            break;
        }
        tmp = tmp->next;
    }
    free(pwd);
}

void    ft_cd(t_list *list_command, t_param *param)
{
    char *path;
    
    if (!list_command->data->arguments)
    {
        path = search_env_var(param, "HOME");
        if (!path)
            error_msg(list_command, list_command->data->cmd, "HOME not set\n", 0);
        else
        {
            if (chdir(path) == -1)
                error_msg(list_command, list_command->data->cmd, strerror(errno), search_env_var(param, "HOME"));
            free(path);
        }
    }
    else
        cd_with_arg(list_command, param);
}
