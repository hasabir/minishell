/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:35:06 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/31 22:46:47 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

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

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*p;
	size_t	i;
	size_t	j;
	char *str;


	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	str = ft_strdup(s2);
	p =malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1) * sizeof(char));
	if (!p)
		return (0);
	i = -1;
	while (++i < ft_strlen((char *)s1))
		p[i] = s1[i];
	j = -1;
	while (++j < ft_strlen(str))
		p[i++] = str[j];
	p[i] = '\0';
	return (p);
}

char	*expand(char *arg, char **env)
{
	int		i;
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
		tmp = ft_strdup(stock[i]);
		env_value = search_env(env, stock[i], &tmp);
		free(stock[i]);
		if (env_value && !ft_isalnum(*tmp))
			stock[i] = ft_strjoin(env_value, tmp);
		else
		{
			if (i != 0 || arg[0] == '$')
			{
				while (*tmp && ft_isalnum(*tmp))
					tmp++;
			}
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
		if (search(stock[i], '$'))
			stock[i] = expand(stock[i], env);
		cmd = ft_strjoin(cmd, stock[i]);
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


int	search_index(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 && s2[i] == 0)
		return (0);
	if (s1[i] == 0 && s2[i] == 0)
		return (0);
	// if (!*s2)
		// return ((char *)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (s1[i + j] && s2[j] && s2[j] == s1[i + j]
			&& i + j < len)
			j++;
		if (s2[j] == 0)
			return (i);
		i++;
	}
	return (0);
}