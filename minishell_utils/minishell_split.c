/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:01:39 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/23 11:23:33 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"

static int	ft_lenmat(char const *s, char c)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			len++;
		while (s[i] != c && s[i])
			i++;
	}
	return (len);
}

static int	ft_lenword(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*ft_alloc(char const *s, char c, char **p, int k)
{
	int	i;
	int	j;

	i = ft_lenword(s, c);
	p[k] = (char *)ft_calloc(i + 1, sizeof (char));
	if (!p[k])
	{
		j = 0;
		while (j++ < k)
			free(p[j]);
		free(p);
		return (0);
	}
	return (p[k]);
}

static char	**fill(char const *s, char c, char **p, int h)
{
	int	i;
	int	a;
	int	j;

	i = -1;
	while (s[h] && ++i < ft_lenmat(s, c))
	{
		while (s[h] == c)
			h++;
		if (s[h] != c)
		{
			ft_alloc(s + h, c, p, i);
			if (!p)
				return (0);
		}	
		a = ft_lenword(s + h, c);
		j = -1;
		h -= 1;
		while (s[++h] != c && ++j < a)
			p[i][j] = s[h];
	}
	return (p);
}

char	**ft_split_v2(char *str, char c, char c2)
{
	char	**matrix;
	int		i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == c2)
			str[i] = c;
	}
	matrix = (char **)ft_calloc(ft_lenmat(str, c) + 1, sizeof (char *));
	if (!matrix)
		return (0);
	matrix = fill(str, c, matrix, 0);
	return (matrix);
}
