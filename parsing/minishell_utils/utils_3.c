/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:56:52 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/03 17:58:53 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int search(char *str, char c)
{
	int i;
	int counter;

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

char	*search_env(char **env, char *to_find, char **tmp)
{
	int		j;
	char	*str;
	int		i;
	int		n;

	i = 0;
	str = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && to_find[j] && env[i][j] == to_find[j])
			j++;
		if (env[i][j] == '=')
		{
			n = -1;
			while (++n < j && tmp && *tmp)
				(*tmp)++;
			str = env[i];
			j++;
			return (str + j);
		}
		i++;
	}
	return (0);
}

int ft_error(int n, char option, char *str_option)
{
	if (option && !str_option)
		printf("Petit_shell: syntax error near unexpected token `%c'\n", option);
	else if (str_option && !option)
		printf("Petit_shell: syntax error near unexpected token `%s'\n", str_option);
	else
	{
		if (n == 0)
			printf("Petit_shell: syntax error near unexpected token `%c'\n", option);
		else if (n == 1)
			printf("Petit_shell: syntax error near unexpected token `%s'\n", str_option);
	}
	return (-1);
}

void	ft_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free (str);
}

void	ft_list_last(t_list **lst, t_list *new)
{
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	(*lst)->next = new;
	(*lst) = new;
}