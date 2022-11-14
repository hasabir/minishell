/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:49:46 by namine            #+#    #+#             */
/*   Updated: 2022/11/14 16:08:47 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

int	is_builtins(char *cmd)
{
	return (
	!ft_strcmp(cmd, "echo") ||
	!ft_strcmp(cmd, "cd") ||
	!ft_strcmp(cmd, "pwd") ||
	!ft_strcmp(cmd, "export") ||
	!ft_strcmp(cmd, "unset") ||
	!ft_strcmp(cmd, "env") ||
	!ft_strcmp(cmd, "exit"));
}

void execute_builtins(t_list *list_command, t_param *param)
{
	if (!ft_strcmp(list_command->data->cmd, "echo"))
		ft_echo(list_command);
	if (!ft_strcmp(list_command->data->cmd, "cd"))
		ft_cd(list_command, param);
	if (!ft_strcmp(list_command->data->cmd, "pwd"))
		ft_pwd(list_command);
	if (!ft_strcmp(list_command->data->cmd, "export"))
		ft_export(list_command, param);
	if(!ft_strcmp(list_command->data->cmd, "unset"))
		ft_unset(list_command, param);
	if (!ft_strcmp(list_command->data->cmd, "env"))
		ft_env(list_command, param);
	if (!ft_strcmp(list_command->data->cmd, "exit"))
		ft_exit(list_command);
}

void ft_dup(t_list *list_command, int fd[2], int save)
{
	if (list_command->next)
	{
		dup2(fd[1], 1);
		close (fd[1]);
	}
	if (save != -1)
	{	
		dup2(save, 0);
		close (save);
	}
	if(list_command->data->output_file != 1)
	{
		dup2(list_command->data->output_file, 1);
		close(list_command->data->output_file);
	}
	if(list_command->data->input_file != 0)
	{
		dup2(list_command->data->input_file, 0);
		close(list_command->data->input_file);
	}
}

int is_absolute_path(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void execution(t_list *list_command, t_param *param)
{
	int		save;
	
	save = -1;
	if (!list_command->next && is_builtins(list_command->data->cmd))
		execute_builtins(list_command, param);
	else
		multiple_pipes(list_command, param, save);
}
