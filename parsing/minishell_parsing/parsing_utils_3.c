/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:26:43 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/05 18:23:46 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	need_to_be_moved(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (search(str, '<') == 0 && search(str, '>') == 0)
		return (1);
	if ((len == 1  && (str[0] == '>'|| str[0] == '<'))
		|| ft_strncmp(str, "<<", len) == 0
		|| ft_strncmp(str, ">>", len) == 0)
		return (0);
	if (str[--len] == '>' || str[len] == '<')
		return (-1);
	return (1);
}

void	skip_indirections(char **matrix_command_line, int **j)
{
	while (matrix_command_line[**j])
	{
		if (need_to_be_moved(matrix_command_line[**j]) == 0)
		{
			free(matrix_command_line[**j]);
			(**j)++;
		}
		else if (search(matrix_command_line[**j], '>')
			|| search(matrix_command_line[**j], '<'))
		{
			if (!(matrix_command_line[**j][0] == '>'
				|| matrix_command_line[**j][0] == '<'))
			{
				ft_get_str(&matrix_command_line[**j]);
				return ;
			}
		}
		else
 			return ;
		if (need_to_be_moved(matrix_command_line[**j]) == -1)
		{
			free(matrix_command_line[**j]);
			(**j)++;
		}
		free(matrix_command_line[**j]);
		(**j)++;
	}
}

int	get_length_options(char **matrix_command_line, int j)
{
	int	count;
	if (!matrix_command_line[j])
		return (0);
	count = 0;
	while (matrix_command_line[j])
	{
		if (search_characters(matrix_command_line[j]) == 1
			&& matrix_command_line[j][0] == '-')
			count++;
		j++;
	}
	return (count);
}

int	get_length_arguments(char **matrix_command_line, int j)
{
	int	count;
	if (!matrix_command_line[j])
		return (0);
	count = 0;
	while (matrix_command_line[j])
	{
		count++;
		j++;
	}
	return (count);
}