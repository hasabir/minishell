/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:51:37 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/28 13:08:51 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	take_out_file(t_list *list_command, char *matrix_input)
{
	int	out_type;
	matrix_input++;
	if (*matrix_input && *matrix_input == '>')
	{
		out_type = 2;
		matrix_input++;
	}
	else
		out_type = 1;
	while (is_space(*matrix_input))
		matrix_input++;
	if (!open_out_file(list_command, matrix_input, out_type))
		return (0);
	return (1);
}

int	take_in_file(t_list *list_command, char *matrix_input)
{
	int	in_type;
	
	matrix_input++;
	if (*matrix_input && *matrix_input == '<')
	{
		in_type = 2;
		matrix_input++;
	}
	else
		in_type = 1;
	while (is_space(*matrix_input))
		matrix_input++;
	if (!open_in_file(list_command, matrix_input, in_type))
		return (0);
	return (1);
}


int take_in_out_files(t_list *list_command, char *matrix_input)
{
	int		i;
	int		return_value;
	char	*matrix_input_ptr;

	i = 0;
	matrix_input_ptr = matrix_input;
	while (*matrix_input_ptr)
	{
		if (*matrix_input_ptr == '>')
		{
			return_value = take_out_file(list_command, matrix_input_ptr);
			if (!return_value)
				return (0);
		}
		else if (*matrix_input_ptr == '<')
		{
			return_value = take_in_file(list_command, matrix_input_ptr);
			if (!return_value)
				return (0);
		}
		if (*matrix_input_ptr)
			matrix_input_ptr++;
	}
		return (1);
// 	// free(file_name);
}





































































// int	take_in_files(t_list *list_command, char **matrix_command_line, int *j, int flag)
// {
// 	int		i;
// 	char	**stock;
// 	int		index;
// 	int		tmp;
// 	int		return_value;

// 	tmp = *j;
// 	return_value = split_in_redirection(&stock ,matrix_command_line, &j, flag);
// 	if (return_value == -1)
// 		return (-1);
// 	i = -1;
// 	while (stock[++i])
// 	{
// 		index = search_index(matrix_command_line[*j], stock[i]
// 							, ft_strlen(matrix_command_line[*j]));
// 		if (index || tmp != *j || flag == 1)
// 			list_command->data->in_file_name
// 				= open_in_files(list_command, matrix_command_line[*j], stock[i], index);
// 		if (!list_command->data->in_file_name)
// 			return(-2);
// 	}
// 	return (return_value);
// }

// int	take_out_files(t_list *list_command, char **matrix_command_line, int *j, int flag)
// {
// 	int		i;
// 	char	**stock;
// 	int		index;
// 	int		tmp;
// 	int		return_value;

// 	tmp = *j;
// 	return_value = split_out_redirection(&stock ,matrix_command_line, &j, flag);
// 	if (return_value == -1)
// 		return (-1);
// 	i = -1;
// 	while (stock[++i])
// 	{
// 		index = search_index(matrix_command_line[*j], stock[i]
// 							, ft_strlen(matrix_command_line[*j]));
// 		if (index || tmp != *j || flag == 1)
// 			list_command->data->out_file_name
// 				= open_out_files(list_command, matrix_command_line[*j], stock[i], index);
// 	}
// 	return (return_value);
// }

// int	take_out_in_files(t_list *list_command, char **matrix_command_line)
// {
// 	int	i;
// 	int	return_value;
	
// 	i = -1;
// 	return_value = 0;
// 	while (return_value != -1 && matrix_command_line[++i])
// 	{
// 		//if (search(matrix_command , '<') && search(matrix_command_line, '>'))
// 		if (search(matrix_command_line[i], '<'))
// 		{
// 			return_value = take_in_files(list_command, matrix_command_line, &i, 0);
// 			if (return_value == -2)
// 				return (0);
// 			while(return_value == 0)
// 			{
// 				i++;
// 				return_value = take_in_files(list_command, matrix_command_line, &i, 1);
// 			}
// 		}
// 		// if (search(matrix_command_line[i], '>'))
// 		// {
// 		// 	return_value = take_out_files(list_command, matrix_command_line, &i, 0);
// 		// 	while (return_value == 0)
// 		// 	{
// 		// 		i++;
// 		// 		return_value = take_out_files(list_command, matrix_command_line, &i, 1);
// 		// 	}
// 		// }
// 	}
// 	// i need to make them in the same while
// 	i = -1;
// 	return_value = 0;
// 	while ( return_value != -1 && matrix_command_line[++i])
// 	{
// 		if (search(matrix_command_line[i], '>'))
// 		{
// 			return_value = take_out_files(list_command, matrix_command_line, &i, 0);
// 			while (return_value == 0)
// 			{
// 				i++;
// 				return_value = take_out_files(list_command, matrix_command_line, &i, 1);
// 			}
// 		}
// 	}
// 	// printf("\n\033[95m-------------------------------\033[00m\n");
// 	// if (list_command->data->in_file_name)
// 	// 	printf("input_file_name = %s\n", list_command->data->in_file_name);
// 	// printf("input_file = %d\n", list_command->data->input_file);
// 	// printf("\n\033[95m-------------------------------\033[00m\n");
// 	// if (list_command->data->out_file_name)
// 	// 	printf("output_file_name = %s\n", list_command->data->out_file_name);
// 	// printf("output_file = %d\n", list_command->data->output_file);	
// 	// free(file_name);
// 	return (1);
// }
