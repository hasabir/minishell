/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:35:06 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/14 15:47:51 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*new_arg(char *stock, char *arg, int flag)
{
	char	*tmp;

	tmp = ft_strdup(arg);
	free(arg);
	arg = ft_strjoin(tmp, stock);
	if (!flag)
		free(stock);
	free(tmp);
	return (arg);
}

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
	else if (*tmp == '?')
	{
		*stock = ft_itoa(g_global.exit_status);
		if (tmp[1])
			*stock = new_arg(tmp + 1, *stock, 1);
	}
	else
	{
		if (i != 0 || arg[0] == '$')
			tmp = get_str(tmp, -1);
		*stock = ft_strdup(tmp);
	}
	free(tmp);
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
			arg = new_arg(stock[i], arg, 0);
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
	{
		cmd = expand(cmd, env);
		if (!*cmd)
			return (cmd);
	}
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
	ft_free(stock);
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
	ft_free(stock);
	return (cmd);
}
