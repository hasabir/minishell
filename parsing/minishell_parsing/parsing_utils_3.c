/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:26:43 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/28 13:09:56 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	skip_indirections(char **matrix_command_line, int **j)
{
	int	len;

	while (matrix_command_line[**j])
	{
		len = ft_strlen(matrix_command_line[**j]);
		if (len == 1 && (matrix_command_line[**j][0] == '>'
			|| matrix_command_line[**j][0] == '<'))
			(**j)++;
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
		(**j)++;
	}
}