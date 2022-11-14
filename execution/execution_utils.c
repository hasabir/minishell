/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:54:13 by namine            #+#    #+#             */
/*   Updated: 2022/11/14 14:19:10 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

void relative_path(t_list *list_command, char **ptr_env)
{
	char *path;
	
	if (path_exists(ptr_env) == -1) 
			ft_exit_status(list_command, "No such file or directory", 0, 127);
	else
	{
		path = get_path(ptr_env, list_command->data->cmd);
		if (execve(path, get_args(list_command), ptr_env) == -1)
			ft_exit_status(list_command, "command not found", 0, 127);
	}
}

void absolute_path(t_list *list_command, char **ptr_env)
{
	char *path;
	
	if (access(list_command->data->cmd, F_OK) == -1)
			ft_exit_status(list_command, "No such file or directory", 0, 127);
		else if (access(list_command->data->cmd, X_OK) == -1)
			ft_exit_status(list_command, "Permission denied", 0, 126);
		else if (chdir(list_command->data->cmd) == 0)
			ft_exit_status(list_command, "is a directory", 0, 126);
		// else if (chdir(list_command->data->cmd) ==  -1)
		// 	ft_exit_status(list_command, "Not a directory", 0, 126); // ???????????????
		else
		{
			path = ft_strdup(list_command->data->cmd);
			if (path != NULL)
			{
				printf("toto\n");
				if (execve(path, get_args(list_command), ptr_env) == -1) //pppp search IN PWD if path in not set
					ft_exit_status(list_command, strerror(errno), 0, 0);
			}
		}
}

void execute_cmd(t_list *list_command, t_param *param)
{
	char **ptr_env;
	
	ptr_env = convert_to_arr(param);
	if (is_builtins(list_command->data->cmd) == 1)
		execute_builtins(list_command, param);
	else if (list_command->data->cmd)
	{	
		if (!is_absolute_path(list_command->data->cmd))
			relative_path(list_command, ptr_env);
		else
			absolute_path(list_command, ptr_env);
	}
}

void	ft_wait(int pid)
{
	int status;

	while(waitpid(pid, &status, 0) != -1);
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
	while(waitpid(-1, NULL, 0) != -1);
	signal(SIGINT, handle_signals);
}

void execute_child(t_list *list_command, t_param *param, int fd[2], int save)
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
			return (ft_exit_status(list_command, strerror(errno), 0, 1));
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
