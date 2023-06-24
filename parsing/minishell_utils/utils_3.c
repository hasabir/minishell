/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:56:52 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/15 03:42:57 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	search(char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

char	*get_str(char *str, int j)
{
	int		n;
	char	*stock;
	char	*str_ptr;

	str_ptr = str;
	if (j == -1)
	{
		while (*str && (ft_isalnum(*str) || *str == '_'))
			str++;
	}
	else
	{
		n = -1;
		while (str && *str && ++n < j)
			str++;
	}
	stock = ft_strdup(str);
	free(str_ptr);
	return (stock);
}

char	*search_env(char **env, char *to_find, char **tmp)
{
	int		j;
	char	*str;
	int		i;

	i = 0;
	str = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && to_find[j] && env[i][j] == to_find[j])
			j++;
		if (env[i][j] == '=')
		{
			*tmp = get_str(*tmp, j);
			str = env[i];
			j++;
			return (str + j);
		}
		i++;
	}
	return (0);
}

int	search_characters(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
	{
		if (arg[i] == '|' || arg[i] == '"' || arg[i] == '\''
			|| arg[i] == '>' || arg[i] == '<' || arg[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

int	search_str(const char *s1, const char *s2)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	if (!s1 && s2[i] == 0)
		return (0);
	if (s1[i] == 0 && s2[i] == 0)
		return (0);
	if (s1)
		len = ft_strlen(s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (s1[i + j] && s2[j] && s2[j] == s1[i + j]
			&& i + j < len)
			j++;
		if (s2[j] == 0)
			return (1);
		i++;
	}
	return (0);
}
