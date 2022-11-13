/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:51:07 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/13 19:00:40 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	open_out_type_1(t_list *list_command, char *matrix, char **env)
{
	char	*out_file_name;

	out_file_name = get_file_name(matrix);
	expand_file(&out_file_name, env, 1);
	if (!*out_file_name)
		return (ft_perror(out_file_name, 0));
	list_command->data->output_file
		= open(out_file_name, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (list_command->data->output_file == -1)
		return (ft_perror(out_file_name, 1));
	free(out_file_name);
	return (1);
}

int	open_out_type_2(t_list *list_command, char *matrix, char **env)
{
	char	*out_file_name;

	out_file_name = get_file_name(matrix);
	expand_file(&out_file_name, env, 1);
	if (!*out_file_name)
		return (ft_perror(out_file_name, 0));
	list_command->data->output_file
		= open(out_file_name,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (list_command->data->output_file == -1)
		return (ft_perror(out_file_name, 1));
	free(out_file_name);
	return (1);
}

int	open_in_type_1(t_list *list_command, char *input, char **env)
{
	char	*in_file_name;
	int		n;

	n = 0;
	if (*input == GREAT_REDIRECTION)
	{
		input++;
		n = 1;
	}
	while (is_space(*input))
		input++;
	in_file_name = get_file_name(input);
	expand_file(&in_file_name, env, 1);
	if (!*in_file_name)
		return (ft_perror(in_file_name, 0));
	list_command->data->input_file = open(in_file_name, O_RDONLY);
	if (list_command->data->input_file == -1)
	{
		if (n)
			return (open_file(list_command, in_file_name));
		return (ft_perror(in_file_name, 1));
	}
	free(in_file_name);
	return (1);
}

int	open_out_file(t_list *list_command, char *matrix, int out_type, char **env)
{
	if (out_type == 1)
	{
		if (!open_out_type_1(list_command, matrix, env))
			return (0);
	}
	else
	{
		if (!open_out_type_2(list_command, matrix, env))
			return (0);
	}
	return (1);
}

int	open_in_file(t_list *list_command, char *input, int in_type, char **env)
{
	if (in_type == 1)
	{
		if (!open_in_type_1(list_command, input, env))
			return (0);
	}
	else
	{
		list_command->data->input_file = -1;
		return (-1);
	}
	return (1);
}
