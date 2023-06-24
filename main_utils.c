/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:49:54 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/15 02:00:40 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/execution.h"

int	check_env(t_param *param, char **env, int flag)
{
	if (flag)
	{
		if (!env || !*env)
		{
			param->env = NULL;
			return (0);
		}
	}
	if (!flag)
	{
		if (!env || !*env)
		{
			param->export = NULL;
			return (0);
		}
	}
	return (1);
}

void	initialize_env(t_param *param, char **env, int i)
{
	char	**ptr;
	t_ev	*tmp;

	if (!check_env(param, env, 1))
		return ;
	param->env = malloc(sizeof(t_ev));
	if (!param->env)
		malloc_failed();
	tmp = param->env;
	while (env[++i])
	{
		ptr = ft_split(env[i], '=');
		tmp->env_var = ft_strdup(ptr[0]);
		tmp->value = ft_strdup(ptr[1]);
		ft_free(ptr);
		tmp->next = malloc(sizeof(t_ev));
		if (!tmp->next)
			malloc_failed();
		if (env[i + 1])
			tmp = tmp->next;
		else
			free(tmp->next);
	}
	tmp->next = NULL;
}

void	initialize_export(t_param *param, char **env, int i)
{
	char	**ptr;
	t_ev	*tmp;

	if (!check_env(param, env, 0))
		return ;
	param->export = malloc(sizeof(t_ev));
	if (!param->export)
		malloc_failed();
	tmp = param->export;
	while (env[++i])
	{
		ptr = ft_split(env[i], '=');
		tmp->env_var = ft_strdup(ptr[0]);
		tmp->value = ft_strdup(ptr[1]);
		ft_free(ptr);
		tmp->next = malloc(sizeof(t_ev));
		if (!tmp->next)
			malloc_failed();
		if (env[i + 1])
			tmp = tmp->next;
		else
			free(tmp->next);
	}
	tmp->next = NULL;
}

int	list_len(t_ev *ptr)
{
	t_ev	*tmp;
	int		i;

	tmp = ptr;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**convert_to_arr(t_param *param)
{
	char	**env_arr;
	t_ev	*tmp;
	char	*s1;
	char	*s2;
	int		i;

	if (!param)
		return (NULL);
	env_arr = malloc(sizeof(char *) * (list_len(param->env) + 1));
	if (!env_arr)
		malloc_failed();
	i = 0;
	tmp = param->env;
	while (tmp)
	{
		s1 = ft_strjoin(tmp->env_var, "=");
		s2 = ft_strjoin(s1, tmp->value);
		free(s1);
		env_arr[i] = ft_strdup(s2);
		free(s2);
		tmp = tmp->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
