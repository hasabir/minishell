/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:39:19 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/14 18:43:06 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	if (!s1 && s2[i] == 0)
		return (0);
	if (s1[i] == 0 && s2[i] == 0)
		return ("");
	if (s1)
		len = ft_strlen(s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (s1[i + j] && s2[j] && s2[j] == s1[i + j]
			&& i + j < len)
			j++;
		if (s2[j] == 0)
			return (((char *)s1) + i);
		i++;
	}
	return (0);
}

int	which_type_redirection(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>')
			return (1);
		if (str[i] == '<')
			return (0);
	}
	return (-1);
}

void	ft_get_str(char **matrix_command_line)
{
	char	**stock;

	if (which_type_redirection(*matrix_command_line) == 1)
		stock = ft_split(*matrix_command_line, '>');
	else
		stock = ft_split(*matrix_command_line, '<');
	free(*matrix_command_line);
	*matrix_command_line = ft_strdup(stock[0]);
	ft_free(stock);
}

void	ft_list_last(t_list **lst, t_list *new)
{
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	(*lst)->next = new;
	(*lst) = new;
}

char	*define_single_double_quote(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '"')
			arg[i] = DOUBLE_QUOTE;
		else if (arg[i] == '\'')
			arg[i] = SINGLE_QUOTE;
	}
	return (arg);
}
