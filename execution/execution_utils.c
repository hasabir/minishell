/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:54:13 by namine            #+#    #+#             */
/*   Updated: 2022/11/14 21:28:24 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

void	ft_wait(int pid)
{
	int	status;

	while (waitpid(pid, &status, 0) != -1)
		;
	if (WIFEXITED(status))
		g_global.exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		g_global.exit_status = 128 + WTERMSIG(status);
		if (g_global.exit_status == 131)
		{
			ft_putstr_fd("Quit: ", 1);
			ft_putnbr_fd(g_global.exit_status - 128, 1);
		}
		write (1, "\n", 1);
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
	signal(SIGINT, handle_signals);
}

void	relative_path(t_list *list_command, char **ptr_env)
{
	char	*path;

	if (path_exists(ptr_env) == -1)
		ft_exit_status(list_command, "No such file or directory", 0, 127);
	else
	{
		path = get_path(ptr_env, list_command->data->cmd);
		if (execve(path, get_args(list_command), ptr_env) == -1)
			ft_exit_status(list_command, "command not found", 0, 127);
	}
}

void	absolute_path(t_list *list_command, char **ptr_env)
{
	char	*path;

	if (access(list_command->data->cmd, F_OK) == -1)
		ft_exit_status(list_command, "No such file or directory", 0, 127);
	else if (access(list_command->data->cmd, X_OK) == -1)
		ft_exit_status(list_command, "Permission denied", 0, 126);
	else if (chdir(list_command->data->cmd) == 0)
		ft_exit_status(list_command, "is a directory", 0, 126);
	else
	{
		path = ft_strdup(list_command->data->cmd);
		if (path != NULL)
		{
			if (execve(path, get_args(list_command), ptr_env) == -1)
				ft_exit_status(list_command, strerror(errno), 0, 0);
		}
	}
}

int	is_absolute_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	path_exists(char **ptr_env)
{
	int	i;

	i = 0;
	while (ptr_env[i])
	{
		if (!ft_strncmp("PATH", ptr_env[i], 4))
			return (i);
		i++;
	}
	return (-1);
}
