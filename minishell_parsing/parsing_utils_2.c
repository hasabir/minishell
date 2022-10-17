/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:35:06 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/17 11:54:18 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_space(char *arg)
{
	int	i;

	i = 0;
	while(arg[i] != '$')
		i++;
	i++;
	if (!arg[i])
		return (1);
	return (0);
}

char	*expand(char *arg, char **env)
{
	int		i;
	int		j;
	char	**stock;
	char	*tmp;
	char	*env_value;
	
	i = -1;
	if (check_space(arg))
		return (arg);
	stock = ft_split(arg, '$');
	i = -1;
	while (stock[++i])
	{
		tmp = stock[i];
		env_value = search_env(env, stock[i], &tmp);
		free(stock[i]);
		if (env_value && !ft_isalnum(*tmp))
				stock[i] = ft_strjoin(env_value, tmp);
		else
		{
			j = 0;
			while (*tmp && ft_isalnum(*tmp))
				tmp++;
			stock[i] = ft_strdup(tmp);
		}
	}
	free(arg);
	i = -1;
	while (stock[++i])
	{
		if (i == 0)
			arg = stock[i];
		else
			arg = ft_strjoin(arg, stock[i]);
	}
	ft_free(stock);
	return (arg);
}

char	*ft_double_quote(char *cmd, char **env)
{
	int		i;
	char	**stock;

	stock = ft_split(cmd, '"');	
	free(cmd);
	cmd = NULL;
	i = -1;
	while (stock[++i])
	{
		if (search(stock[i], '$') != 0)
			stock[i] = expand(stock[i], env);
		cmd = ft_strjoin(cmd, stock[i]);
	}
	i = -1;
	while (stock[++i])
		free (stock[i]);
	free(stock);
	return (cmd);
}

char	*ft_single_quote(char *cmd)
{
	int		i;
	char	**stock;

	if (!cmd || !*cmd)
		return (cmd);
	stock = ft_split(cmd, '\'');
	free(cmd);
	cmd = NULL;
	i = -1;
	while (stock[++i])
		cmd = ft_strjoin(cmd, stock[i]);
	i = -1;
	while (stock[++i])
		free (stock[i]);
	free(stock);
	return (cmd);
}
