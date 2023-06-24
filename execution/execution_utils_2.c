/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:54:15 by namine            #+#    #+#             */
/*   Updated: 2022/11/15 02:03:00 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

char	*get_path(char **ptr_env, char *cmd)
{
	char	**paths;
	char	*s;
	int		i;

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
		paths[i] = ft_strjoin(paths[i], cmd);
		if (!access(paths[i], X_OK | F_OK))
			return (paths[i]);
		i++;
	}
	return (NULL);
}

char	**get_args(t_list	*list_command)
{
	char	**argv;
	int		i;
	int		j;

	argv = malloc(sizeof(char *) * (get_len(list_command) + 1));
	if (!argv)
		malloc_failed();
	i = -1;
	if (list_command->data->cmd)
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

int	get_len(t_list	*list_command)
{
	int	count_args;
	int	i;

	count_args = 0;
	if (list_command->data->cmd)
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
		while (list_command->data->arguments[i])
		{
			count_args++;
			i++;
		}
	}
	return (count_args);
}

void	ft_dup(t_list *list_command, int fd[2], int save)
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
	if (list_command->data->output_file != 1)
		dup2(list_command->data->output_file, 1);
	if (list_command->data->input_file != 0)
	{
		dup2(list_command->data->input_file, 0);
		close(list_command->data->input_file);
	}
}

void	execute_cmd(t_list *list_command, t_param *param)
{
	char	**ptr_env;

	ptr_env = convert_to_arr(param);
	if (is_builtins(list_command->data->cmd) == 1)
		execute_builtins(list_command, param, 0);
	else if (list_command->data->cmd)
	{	
		if (!is_absolute_path(list_command->data->cmd))
			relative_path(list_command, ptr_env);
		else
			absolute_path(list_command, ptr_env);
	}
}
