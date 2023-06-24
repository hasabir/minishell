/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:43 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/15 01:02:28 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	ft_perror(char *str, int flag)
{
	g_global.exit_status = 1;
	if (!flag && !str)
	{
		write(2, "Petit_shell: ", 14);
		perror(NULL);
		return (0);
	}
	else if (!flag)
	{
		write(2, "Petit_shell: ", 14);
		write(2, str, ft_strlen(str));
		write(2, "ambiguous redirect\n", 20);
		free(str);
		return (0);
	}
	if (flag == 1 || flag == 2)
	{
		write(2, "Petit_shell: ", 14);
		write(2, str, ft_strlen(str));
		perror(" ");
		if (flag == 1)
			free(str);
		return (0);
	}
	return (1);
}

int	ft_error(int n, char option, char *str_option, char *input)
{
	g_global.exit_status = n;
	if (option && !str_option)
	{
		ft_putstr_fd("Petit_shell: syntax error near unexpected token `", 2);
		ft_putchar_fd(option, 2);
		ft_putstr_fd("\'\n", 2);
	}
	if (!option && str_option)
	{
		ft_putstr_fd("Petit_shell: syntax error near unexpected token `", 2);
		ft_putstr_fd(str_option, 2);
		ft_putstr_fd("\'\n", 2);
	}
	else if (!option && !str_option)
	{
		write (2, "Petit_shell: : No such file or directory\n", 42);
		return (0);
	}
	free(input);
	return (-1);
}

char	*error(char *str)
{	
	write(2, "Petit_shell: ", 14);
	if (!str)
		perror(NULL);
	return (NULL);
}

int	ft_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free (str);
	return (0);
}
