/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:49:46 by namine            #+#    #+#             */
/*   Updated: 2022/11/11 09:42:56 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int path_exists(char **ptr_env)
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

char	*get_path(char **ptr_env, char *str)
{
	char **paths;
	int i;
	char *s;

	if (*str == '/' || *str == '.') // check stat function
		return (str);
	i = path_exists(ptr_env);
	if (i == -1)
		return (NULL);
	s = ft_strdup(ptr_env[i]);
	while (*s && *s != '=')
		s++;
	s++;
	paths = ft_split(s, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], str);
		if (!access(paths[i], X_OK)) // x_ok ?
			return (paths[i]);
		i++;
	}
	return (NULL);
}

int		get_len(t_list	*list_command)
{
	int count_args;
	int i;
	
	count_args = 0;
	if(list_command->data->cmd)
		count_args++;
	i = 0;
	if (list_command->data->options)
	{
		while (list_command->data->options[i])
		{
			count_args++;
			i++;
		}
	}
	i = 0;
	if (list_command->data->arguments)
	{
		if (list_command->data->arguments[i])
		{
			count_args++;
			i++;
		}
	}
	return (count_args);
}

char	**get_args(t_list	*list_command)
{
	char	**argv;
	int		i;
	int		j;

	argv = malloc(sizeof(char *) * (get_len(list_command) + 1));
	if (!argv)
		return (NULL);
	i = -1;
	if(list_command->data->cmd)
		argv[++i] = ft_strdup(list_command->data->cmd);
	i++;
	j = -1;
	if (list_command->data->options)
	{
		while (list_command->data->options[++j])
			argv[i++] = ft_strdup(list_command->data->options[j]);
	}
	j = -1;
	if (list_command->data->arguments)
	{
		while (list_command->data->arguments[++j])
			argv[i++] = ft_strdup(list_command->data->arguments[j]);		
	}
	argv[i] = NULL;
	return (argv);
}

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
		ft_pwd(list_command, param);
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
		dup2(list_command->data->output_file, 1);
	if(list_command->data->input_file != 0)
	{
		dup2(list_command->data->input_file, 0);
		close(list_command->data->input_file);
	}
}

void execute_cmd(char **ptr_env, t_list *list_command, t_param *param)
{
	char	*path;
	
	if (is_builtins(list_command->data->cmd) == 1)
		execute_builtins(list_command, param);
	else if (list_command->data->cmd)
	{
		if (path_exists(ptr_env) == -1)
			error_msg(list_command, list_command->data->cmd, "No such file or directory\n", 0);
		else 
		{
			path = get_path(ptr_env, list_command->data->cmd);
			if (execve(path, get_args(list_command), ptr_env) == -1)
				error_msg(list_command, list_command->data->cmd, "command not found\n", 0);
		}
	}
}

void multiple_pipes(char **ptr_env, t_list *list_command, t_param *param, int save)
{
	int		fd[2];
	int		pid;
	
	while (list_command)
	{
		if (pipe(fd) == -1)
			return ;
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
		{
			close(fd[0]);
			ft_dup(list_command, fd, save);
			execute_cmd(ptr_env, list_command, param);
			exit(127);
		}
		if (save != -1)
			close (save);
		save = fd[0];
		close (fd[1]);
		list_command = list_command->next;
	}
	close (fd[0]);
	while(waitpid(-1, NULL, 0) != -1);
}

void execution(t_list *list_command, char **ptr_env, t_param *param)
{
	int		save;
	
	save = -1;
	if (ft_lstsize((t_linked_list *)list_command) == 1 && is_builtins(list_command->data->cmd))
		execute_builtins(list_command, param);
	else
		multiple_pipes(ptr_env, list_command, param, save);
}
// wait for the last pipe
// get exit code
