/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:56:52 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/07 10:28:05 by hasabir          ###   ########.fr       */
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

char *get_str(char *str, int j)
{
	int		n;
	char	*stock;
	char	*str_ptr;

	str_ptr = str;
	if (j == -1)
	{
		if (*str && ft_isdigit(*str))
			str++;
		else
		{
			while (*str && (ft_isalnum(*str) || *str == '_'))
				str++;
		}
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

int ft_error(int n, char option, char *str_option, char *input)
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
	free(input);
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