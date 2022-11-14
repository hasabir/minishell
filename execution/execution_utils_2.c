/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:54:15 by namine            #+#    #+#             */
/*   Updated: 2022/11/14 13:09:37 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

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

char	*get_path(char **ptr_env, char *cmd)
{
	char **paths;
	char *s;
	int i;
	
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
		if (!access(paths[i], X_OK | F_OK)) // x_ok ? and f_ok
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