/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 04:49:41 by namine            #+#    #+#             */
/*   Updated: 2022/11/14 19:21:31 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

void	change_directoty(t_list *list_command)
{
	if (chdir(list_command->data->arguments[0]) == -1)
	{
		if (open(list_command->data->arguments[0], O_RDONLY) != -1)
			ft_exit_status(list_command, "Not a directory",
				list_command->data->arguments[0], 1);
		else
			ft_exit_status(list_command, strerror(errno),
				list_command->data->arguments[0], 1);
	}	
}

void	cd_with_arg(t_list *list_command, t_param *param)
{
	char	*oldpwd;
	t_ev	*list;
	char	*pwd;

	(void)list_command;
	oldpwd = getcwd(NULL, 0);
	list = param->env;
	free_env_var_and_replace(list, "OLDPWD", oldpwd);
	list = param->export;
	free_env_var_and_replace(list, "OLDPWD", oldpwd);
	free(oldpwd);
	change_directoty(list_command);
	pwd = getcwd(NULL, 0);
	list = param->env;
	free_env_var_and_replace(list, "PWD", pwd);
	list = param->export;
	free_env_var_and_replace(list, "PWD", pwd);
	free(pwd);
	g_global.exit_status = 0;
}

void	ft_cd(t_list *list_command, t_param *param)
{
	char	*path;

	if (!list_command->data->arguments)
	{
		path = search_env_var(param->env, "HOME");
		if (!path)
			ft_exit_status(list_command, "HOME not set", 0, 1);
		else
		{
			if (chdir(path) == -1)
				ft_exit_status(list_command, strerror(errno),
					search_env_var(param->env, "HOME"), 1);
			else
				g_global.exit_status = 0;
			free(path);
		}
	}
	else
		cd_with_arg(list_command, param);
}
