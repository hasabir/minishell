/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:35:06 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/11 10:22:31 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	expand_stock(int i, char *arg, char **stock, char **env)
{
	char	*tmp;
	char	*env_value;

	tmp = ft_strdup(*stock);
	env_value = search_env(env, *stock, &tmp);
	free(*stock);
	if (env_value && *tmp != '_' && !ft_isalnum(*tmp))
	{
		env_value = define_single_double_quote(env_value);
		*stock = ft_strjoin(env_value, tmp);
	}
	else
	{
		if (i != 0 || arg[0] == '$')
			tmp = get_str(tmp, -1);
		*stock = ft_strdup(tmp);
	}
	free(tmp);
}

char	*new_arg(char *stock, char *arg)
{
	char	*tmp;

	tmp = ft_strdup(arg);
	free(arg);
	arg = ft_strjoin(tmp, stock);
	free(tmp);
	free(stock);
	return (arg);
}

char	*expand(char *arg, char **env)
{
	int		i;
	char	**stock;

	stock = ft_split(arg, '$');
	i = -1;
	while (stock[++i])
		expand_stock(i, arg, &stock[i], env);
	free(arg);
	i = -1;
	while (stock[++i])
	{
		if (i == 0)
			arg = stock[i];
		else
			arg = new_arg(stock[i], arg);
	}
	free(stock);
	return (arg);
}

char	*ft_double_quote(char *cmd, char **env, int n)
{
	int		i;
	char	**stock;
	char	*tmp;

	if (n && search(cmd, '$'))
		cmd = expand(cmd, env);
	stock = ft_split(cmd, '"');
	free(cmd);
	cmd = NULL;
	i = -1;
	while (stock[++i])
	{
		tmp = ft_strdup(cmd);
		free(cmd);
		cmd = ft_strjoin(tmp, stock[i]);
		free(tmp);
	}
	i = -1;
	while (stock[++i])
		free (stock[i]);
	free(stock);
	if (!cmd)
		cmd = ft_strdup("\0");
	return (cmd);
}

char	*ft_single_quote(char *cmd)
{
	int		i;
	char	**stock;
	char	*tmp;

	if (!cmd || !*cmd)
		return (cmd);
	stock = ft_split(cmd, '\'');
	free(cmd);
	cmd = NULL;
	i = -1;
	while (stock[++i])
	{
		tmp = ft_strdup(cmd);
		free(cmd);
		cmd = ft_strjoin(tmp, stock[i]);
		free(tmp);
	}
	i = -1;
	while (stock[++i])
		free (stock[i]);
	free(stock);
	return (cmd);
}
