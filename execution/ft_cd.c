/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 04:49:41 by namine            #+#    #+#             */
/*   Updated: 2022/11/12 21:54:21 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

void cd_with_arg(t_list *list_command, t_param *param)
{
    (void)param;
    char    *oldpwd;
    t_ev    *list;
    char    *pwd;
    
    oldpwd = getcwd(NULL, 0);
    list = param->env;
    free_env_var_and_replace(list, "OLDPWD", oldpwd);
    list = param->export;
    free_env_var_and_replace(list, "OLDPWD", oldpwd);
    free(oldpwd);
    if (chdir(list_command->data->arguments[0]) == -1)
        error_msg(list_command, list_command->data->cmd, "not found\n", list_command->data->arguments[0]);
    pwd = getcwd(NULL, 0);
    list = param->env;
    free_env_var_and_replace(list, "PWD", pwd);
    list = param->export;
    free_env_var_and_replace(list, "PWD", pwd);
    free(pwd);
}

void    ft_cd(t_list *list_command, t_param *param)
{
    char *path;
    
    if (!list_command->data->arguments)
    {
        path = search_env_var(param->env, "HOME");
        if (!path)
            error_msg(list_command, list_command->data->cmd, "HOME not set\n", 0);
        else
        {
            if (chdir(path) == -1)
                error_msg(list_command, list_command->data->cmd, strerror(errno), search_env_var(param->env, "HOME"));
            free(path);
        }
    }
    else
        cd_with_arg(list_command, param);
}
