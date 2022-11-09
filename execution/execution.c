/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:49:46 by namine            #+#    #+#             */
/*   Updated: 2022/11/09 06:47:05 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

char	*get_path(char **ptr_env, char *str)
{
	char **paths;
	int i;
	int j;
	
	if (*str == '/' || *str == '.')
		return (str);
	i = 0;
	while (ptr_env[i])
	{
		if (!strncmp("PATH", ptr_env[i], 4))
			break;
		i++;
	}
	j = 0;
	while (ptr_env[i][j] != '=')
		j++;
	j++;
	paths = ft_split(ptr_env[i], ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], str);
		i++;
	}
	i = 0;
	while (paths[i] && access(paths[i], X_OK))
		i++;
	return (paths[i]);
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
	i = 0;
	if(list_command->data->cmd)
	{
		argv[i] = ft_strdup(list_command->data->cmd);
		i++;
	}
	j = 0;
	if (list_command->data->options)
	{
		while (list_command->data->options[j])
		{
			argv[i] = ft_strdup(list_command->data->options[j]);
			i++;
			j++;
		}
	}
	j = 0;
	if (list_command->data->arguments)
	{
		while (list_command->data->arguments[j])
		{
			argv[i] = ft_strdup(list_command->data->arguments[j]);
			j++;
			i++;
		}		
	}
	argv[i] = NULL;
	return (argv);
}

int	is_builtins(char *cmd)
{
	return (
	!ft_strncmp(cmd, "echo", 5) ||
	!ft_strncmp(cmd, "cd", 3) ||
	!ft_strncmp(cmd, "pwd", 4) ||
	!ft_strncmp(cmd, "export", 7) ||
	!ft_strncmp(cmd, "unset", 6) ||
	!ft_strncmp(cmd, "env", 4) ||
	!ft_strncmp(cmd, "exit", 5));
}

void execute_builtins(t_list *list_command, t_param *param, char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		ft_echo(list_command);
	if (!ft_strncmp(cmd, "cd", 3))
		ft_cd(list_command, param);
	if (!ft_strncmp(cmd, "pwd", 4))
		ft_pwd(list_command, param);
	if (!ft_strncmp(cmd, "export", 7))
		ft_export(list_command, param);
	if(!ft_strncmp(cmd, "unset", 6))
		ft_unset(list_command, param);
	if (!ft_strncmp(cmd, "env", 4))
		ft_env(list_command, param);
	if (!ft_strncmp(cmd, "exit", 5))
		ft_exit(list_command);
}

void	execution(t_list *list_command, char **ptr_env, t_param *param)
{
	char	*path;
	int		fd[2];
	int		save;
	t_list *tmp;
	
	tmp = list_command;
	save = -1;
	if (ft_lstsize((t_linked_list *)list_command) == 1 && is_builtins(tmp->data->cmd))
		execute_builtins(list_command, param, tmp->data->cmd);
	else{
	while (tmp)
	{
		if (pipe(fd) == -1)
			return ;
		int pid1 = fork();
		if (pid1 < 0)
			return ;
		if (pid1 ==  0)
		{
			close(fd[0]);
			if (tmp->next)
			{
				dup2(fd[1], 1);
				close (fd[1]);	
			}
			if (save != -1)
			{
				dup2(save, 0);
				close (save);
			}
			if(tmp->data->output_file != 1)
				dup2(tmp->data->output_file, 1); // close
			if(tmp->data->input_file != 0)
			{
				dup2(tmp->data->input_file, 0);
				close(tmp->data->input_file);
			}
			if (is_builtins(tmp->data->cmd) == 1)
			{
				execute_builtins(list_command, param, tmp->data->cmd);
				exit(127);
			}
			path = get_path(ptr_env, tmp->data->cmd);
			if (!path)
			{
				write(2, "Petit_shell: ", 14);
				write(2, tmp->data->cmd, ft_strlen(tmp->data->cmd));
				write(2, ": command not found\n", 21);
				exit (127);
			}
			execve(path, get_args(tmp), ptr_env);
			write(2, "Petit_shell: ", 14);
			write(2, tmp->data->cmd, ft_strlen(tmp->data->cmd));
			perror(" ");
			exit(127);
		}
		if (save != -1)
			close (save);
		save = fd[0];
		close (fd[1]);
		tmp = tmp->next;
	}
	close (fd[0]);
	while(waitpid(-1, NULL, 0) != -1);
	}
}
