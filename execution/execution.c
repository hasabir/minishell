/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:49:46 by namine            #+#    #+#             */
/*   Updated: 2022/11/15 01:43:12 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

int	is_builtins(char *cmd)
{
	return (
		!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

void	execute_builtins(t_list *list_command, t_param *param, int print)
{
	if (!ft_strcmp(list_command->data->cmd, "echo"))
		ft_echo(list_command);
	if (!ft_strcmp(list_command->data->cmd, "cd"))
		ft_cd(list_command, param);
	if (!ft_strcmp(list_command->data->cmd, "pwd"))
		ft_pwd(list_command);
	if (!ft_strcmp(list_command->data->cmd, "export"))
		ft_export(list_command, param);
	if (!ft_strcmp(list_command->data->cmd, "unset"))
		ft_unset(list_command, param);
	if (!ft_strcmp(list_command->data->cmd, "env"))
		ft_env(list_command, param);
	if (!ft_strcmp(list_command->data->cmd, "exit"))
		ft_exit(list_command, print);
}

void	execute_child(t_list *list_command, t_param *param, int fd[2], int save)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd[0]);
	ft_dup(list_command, fd, save);
	execute_cmd(list_command, param);
	exit(g_global.exit_status);
}

int	multiple_pipes(t_list *list_command, t_param *param, int save)
{
	int		fd[2];
	int		pid;

	while (list_command)
	{
		if (pipe(fd) == -1)
			return (ft_exit_status(list_command, strerror(errno), 0, 1));
		pid = fork();
		if (pid < 0)
			return (fork_failed("fork", strerror(errno), 1));
		signal(SIGINT, SIG_IGN);
		if (pid == 0)
			execute_child(list_command, param, fd, save);
		if (save != -1)
			close (save);
		save = fd[0];
		close (fd[1]);
		list_command = list_command->next;
	}
	close (fd[0]);
	ft_wait(pid);
	return (1);
}

void	execution(t_list *list_command, t_param *param)
{
	int		save;

	save = -1;
	if (!list_command->next && is_builtins(list_command->data->cmd))
		execute_builtins(list_command, param, 1);
	else
		multiple_pipes(list_command, param, save);
}
