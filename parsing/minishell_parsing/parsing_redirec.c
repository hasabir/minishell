/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:51:37 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/05 18:27:16 by hasabir          ###   ########.fr       */
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
	if (!open_out_file(list_command, matrix_input, out_type, env))
		return (0);
	return (1);
}

int	take_in_file(t_list *list_command, char *matrix_input, char **env)
{
	int	in_type;
	int	return_value;

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
	return_value = open_in_file(list_command, matrix_input, in_type, env);
	if (!return_value)
		return (0);
	return (return_value);
}


int take_in_out_files(t_list *list_command, char *matrix_input, char **env)
{
	int		return_value;
	char	*matrix_input_ptr;

	matrix_input_ptr = matrix_input;
	while (*matrix_input_ptr)
	{
		if (*matrix_input_ptr == '>')
		{
			return_value = take_out_file(list_command, matrix_input_ptr, env);
			if (!return_value)
				return (0);
		}
		else if (*matrix_input_ptr == '<')
		{
			return_value = take_in_file(list_command, matrix_input_ptr, env);
			if (!return_value)
				return (0);
			if (return_value == -1)
				matrix_input_ptr++;
		}
		if (*matrix_input_ptr)
		{
			matrix_input_ptr++;
			// printf("matrix_input = %s\n", matrix_input_ptr);
			// if (return_value == -1)
			// 	matrix_input_ptr++;
		}
	}
		return (1);
}
