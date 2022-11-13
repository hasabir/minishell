/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:51:37 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/13 21:52:08 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	take_out_file(t_list *list_command, char *matrix_input, char **env)
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
	if (list_command->data->output_file != 1)
	{
		if (close(list_command->data->output_file) == -1)
			return (ft_perror(0, 0));
	}
	if (!open_out_file(list_command, matrix_input, out_type, env))
		return (0);
	return (out_type);
}

int	take_in_file(t_list *list_command, char *input, char **env)
{
	int	in_type;
	int	return_value;

	input++;
	if (*input && *input == '<')
	{
		in_type = 2;
		input++;
	}
	else
		in_type = 1;
	while (is_space(*input))
		input++;
	if (list_command->data->input_file != 0
		&& list_command->data->input_file != -1)
	{
		if (close(list_command->data->input_file) == -1)
			return (ft_perror(0, 0));
	}
	return_value = open_in_file(list_command, input, in_type, env);
	if (!return_value)
		return (0);
	return (return_value);
}

int	take_in_out_files(t_list *list_command, char *matrix_input, char **env)
{
	int		return_value;
	char	*matrix_input_ptr;

	matrix_input_ptr = matrix_input;
	return_value = 1;
	while (*matrix_input_ptr)
	{
		if (*matrix_input_ptr == '>')
		{
			return_value = take_out_file(list_command, matrix_input_ptr, env);
			if (return_value == 2)
				matrix_input_ptr++;
		}
		else if (*matrix_input_ptr == '<')
		{
			return_value = take_in_file(list_command, matrix_input_ptr, env);
			if (return_value == -1)
				matrix_input_ptr++;
		}
		if (!return_value)
			return (0);
		if (*matrix_input_ptr)
			matrix_input_ptr++;
	}
	return (1);
}
