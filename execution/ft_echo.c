/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:05:57 by namine            #+#    #+#             */
/*   Updated: 2022/11/04 18:31:39 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	gonna_print(char *str, int *new_line)
{
	if (*str == '-')
	{
		str++;
		if (*str == '\0')
			return (1);
	}
	else
		return (1);
	while (*str && *str == 'n')
		str++;
    if (*str != '\0')
		return (1);
	else
		*new_line = 0;
	return (0);
}

void	print_str(t_list *list_command, int *new_line)
{
	int	i;
	
	i = 0;
	while (list_command->data->options[i] && !gonna_print(list_command->data->options[i], new_line))
		i++;
	while (list_command->data->options[i])
	{
		ft_putstr_fd(list_command->data->options[i], list_command->data->output_file);
		if (list_command->data->options[i + 1] || (list_command->data->arguments))
			ft_putstr_fd(" ", list_command->data->output_file);
		i++;
	}
}

void	ft_echo(t_list *list_command)
{
	int new_line;
	int	i;
	
	new_line = 1;
    if (list_command->data->options)
		print_str(list_command, &new_line);
    if (list_command->data->arguments)
	{
		i = 0;
		while (list_command->data->arguments[i])
		{
			ft_putstr_fd(list_command->data->arguments[i], list_command->data->output_file);
			if (list_command->data->arguments[i + 1])
				ft_putstr_fd(" ", list_command->data->output_file);
			i++;
		}
	}
	if (new_line)
		ft_putstr_fd("\n", list_command->data->output_file);
}
