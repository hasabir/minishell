/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:43 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/10 18:35:01 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	ft_perror(char *str, int flag)
{
	if (!flag)
	{
		write(2, "Petit_shell: ", 14);
		write(2, str,
			ft_strlen(str));
		write(2, "ambiguous redirect\n", 20);
		free(str);
		return (0);
	}
	if (flag == 1 || flag == 2)
	{
		write(2, "Petit_shell: ", 14);
		write(2, str,
			ft_strlen(str));
		perror(" ");
		if (flag == 1)
			free(str);
		return (0);
	}
	return (1);
}

int	ft_error(int n, char option, char *str_option, char *input)
{
	if (option && !str_option)
		printf("Petit_shell: syntax error near unexpected token `%c'\n", option);
	else if (str_option && !option)
		printf("Petit_shell: syntax error near unexpected token `%s'\n",
			str_option);
	else
	{
		if (n == 0)
			printf("Petit_shell: syntax error near unexpected token `%c'\n",
				option);
		else if (n == 1)
			printf("Petit_shell: syntax error near unexpected token `%s'\n",
				str_option);
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
