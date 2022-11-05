/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:49:46 by namine            #+#    #+#             */
/*   Updated: 2022/11/05 10:38:39 by namine           ###   ########.fr       */
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

// void is_builtin(t_list *list_command)
// {
// 	ft_echo(list_command);
// }

void	execution(t_list *list_command, char **ptr_env, t_param *param)
{
	char	*path;
	int		save;
	int		fd[2];
	(void)param;
	
	save = -1;
	// ft_unset(list_command, param);
	// return ;
	while (list_command)
	{
		if (pipe(fd) == -1)
			return ;
		int pid1 = fork();
		if (pid1 < 0)
			return ;
		if (pid1 ==  0)
		{
			close(fd[0]);
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
				dup2(list_command->data->output_file, 1); // close
			if(list_command->data->input_file != 0)
				dup2(list_command->data->input_file, 0);
			path = get_path(ptr_env, list_command->data->cmd);
			if (!path)
			{
				write(2, "Petit_shell: ", 14);
				write(2, list_command->data->cmd, ft_strlen(list_command->data->cmd));
				write(2, ": command not found\n", 21);
				exit (127);
			}
			if (!ft_strncmp(list_command->data->cmd, "echo", 5))
			{
				ft_echo(list_command);
				exit(127);
			}
			execve(path, get_args(list_command), ptr_env);
			write(2, "Petit_shell: ", 14);
			write(2, list_command->data->cmd, ft_strlen(list_command->data->cmd));
			perror(" ");
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
