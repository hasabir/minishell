/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:51:37 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/27 22:37:40 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../minishell.h"
#include "../parsing.h"

int	take_in_files(t_list *list_command, char **matrix_command_line, int *j, int flag)
{
	int		i;
	char	**stock;
	int		index;
	int		tmp;
	int		return_value;

	tmp = *j;
	return_value = split_in_redirection(&stock ,matrix_command_line, &j, flag);
	if (return_value == -1)
		return (-1);
	i = -1;
	while (stock[++i])
	{
		index = search_index(matrix_command_line[*j], stock[i]
							, ft_strlen(matrix_command_line[*j]));
		if (index || tmp != *j || flag == 1)
			list_command->data->in_file_name
				= open_in_files(list_command, matrix_command_line[*j], stock[i], index);
		if (!list_command->data->in_file_name)
			return(-2);
	}
	return (return_value);
}

int	take_out_files(t_list *list_command, char **matrix_command_line, int *j, int flag)
{
	int		i;
	char	**stock;
	int		index;
	int		tmp;
	int		return_value;

	tmp = *j;
	return_value = split_out_redirection(&stock ,matrix_command_line, &j, flag);
	if (return_value == -1)
		return (-1);
	i = -1;
	while (stock[++i])
	{
		index = search_index(matrix_command_line[*j], stock[i]
							, ft_strlen(matrix_command_line[*j]));
		if (index || tmp != *j || flag == 1)
			list_command->data->out_file_name
				= open_out_files(list_command, matrix_command_line[*j], stock[i], index);
	}
	return (return_value);
}

int	take_out_in_files(t_list *list_command, char **matrix_command_line)
{
	int	i;
	int	return_value;
	
	i = -1;
	return_value = 0;
	while (return_value != -1 && matrix_command_line[++i])
	{
		//if (search(matrix_command , '<') && search(matrix_command_line, '>'))
		if (search(matrix_command_line[i], '<'))
		{
			return_value = take_in_files(list_command, matrix_command_line, &i, 0);
			if (return_value == -2)
				return (0);
			while(return_value == 0)
			{
				i++;
				return_value = take_in_files(list_command, matrix_command_line, &i, 1);
			}
		}
		// if (search(matrix_command_line[i], '>'))
		// {
		// 	return_value = take_out_files(list_command, matrix_command_line, &i, 0);
		// 	while (return_value == 0)
		// 	{
		// 		i++;
		// 		return_value = take_out_files(list_command, matrix_command_line, &i, 1);
		// 	}
		// }
	}
	// i need to make them in the same while
	i = -1;
	return_value = 0;
	while ( return_value != -1 && matrix_command_line[++i])
	{
		if (search(matrix_command_line[i], '>'))
		{
			return_value = take_out_files(list_command, matrix_command_line, &i, 0);
			while (return_value == 0)
			{
				i++;
				return_value = take_out_files(list_command, matrix_command_line, &i, 1);
			}
		}
	}
	// printf("\n\033[95m-------------------------------\033[00m\n");
	// if (list_command->data->in_file_name)
	// 	printf("input_file_name = %s\n", list_command->data->in_file_name);
	// printf("input_file = %d\n", list_command->data->input_file);
	// printf("\n\033[95m-------------------------------\033[00m\n");
	// if (list_command->data->out_file_name)
	// 	printf("output_file_name = %s\n", list_command->data->out_file_name);
	// printf("output_file = %d\n", list_command->data->output_file);	
	// free(file_name);
	return (1);
}
