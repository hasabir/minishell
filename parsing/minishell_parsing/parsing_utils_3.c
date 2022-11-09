/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:26:43 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/09 19:57:00 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	need_to_be_moved(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (search(str, '<') == 0 && search(str, '>') == 0)
		return (1);
	if ((len == 1 && (str[0] == '>' || str[0] == '<'))
		|| ft_strncmp(str, "<<", len) == 0
		|| ft_strncmp(str, ">>", len) == 0 || ft_strcmp(str, "<>"))
	{
		free(str);
		return (0);
	}
	return (1);
}

void	skip_redirection(char **matrix, int **j)
{
	while (matrix[**j])
	{
		if (need_to_be_moved(matrix[**j]) == 0)
		{
			if (!matrix[++(**j)])
				return ;
		}
		if (search(matrix[**j], '>') || search(matrix[**j], '>'))
		{
			if (!search(matrix[**j], FILE_NAME) || (matrix[**j][0] != FILE_NAME
				&& (matrix[**j][0] != '<' && matrix[**j][0] != '>')))
			{
				ft_get_str(&matrix[**j]);
				return ;
			}
		}
		if (search(matrix[**j], FILE_NAME))
		{
			free(matrix[**j]);
			if (!matrix[++(**j)])
				return ;
		}
		else
			return ;
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

char	*get_file_name(char	*str)
{
	int		i;
	int		len;
	char	*file_name;

	len = 0;
	while (str[len] && str[len] != '>'
		&& str[len] != '<' && !is_space(str[len]))
		len++;
	file_name = malloc(sizeof(char) * (len + 1));
	i = -1;
	while (++i < len)
	{
		file_name[i] = str[i];
		str[0] = FILE_NAME;
	}
	file_name[i] = '\0';
	return (file_name);
}
