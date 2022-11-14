/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:51:50 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/14 18:41:40 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	take_cmd(t_list *list_command, char **matrix_command_line, int *j)
{
	skip_redirection(matrix_command_line, &j);
	matrix_command_line[*j]
		= set_redirection_to_origin(matrix_command_line[*j]);
	(list_command)->data->cmd = ft_strdup(matrix_command_line[*j]);
	free(matrix_command_line[*j]);
	if (matrix_command_line[*j])
		(*j)++;
	return ;
}

void	take_options(t_list *list_command, char **matrix, int *j)
{
	int	i;
	int	len;

	i = 0;
	len = get_length_options(matrix, *j);
	if (!len)
		return ;
	(list_command)->data->options = malloc((len + 2) * sizeof(char *));
	if (!list_command->data->options)
		malloc_failed();
	while (matrix[*j])
	{
		skip_redirection(matrix, &j);
		if (search_characters(matrix[*j]) == 1 && matrix[*j][0] == '-')
		{
			matrix[*j] = set_redirection_to_origin(matrix[*j]);
			(list_command)->data->options[i] = ft_strdup(matrix[*j]);
			free(matrix[*j]);
			i++;
			(*j)++;
		}
		else
			break ;
	}
	list_command->data->options[i] = NULL;
}

void	take_argument(t_list *list_command, char **matrix_command_line, int *j)
{
	int	i;
	int	len;

	i = 0;
	skip_redirection(matrix_command_line, &j);
	len = get_length_arguments(matrix_command_line, *j);
	if (!len)
		return ;
	list_command->data->arguments = malloc((len + 1) * sizeof(char *));
	if (!list_command->data->arguments)
		malloc_failed();
	while (matrix_command_line[*j])
	{
		matrix_command_line[*j]
			= set_redirection_to_origin(matrix_command_line[*j]);
		(list_command)->data->arguments[i] = ft_strdup(matrix_command_line[*j]);
		free(matrix_command_line[*j]);
		i++;
		(*j)++;
		skip_redirection(matrix_command_line, &j);
	}
	list_command->data->arguments[i] = NULL;
	return ;
}

void	set_arg(char ***matrix_command_line, char **env)
{
	int	i;

	i = 0;
	(void)env;
	while (*(*matrix_command_line + i))
	{
		*(*matrix_command_line + i)
			= ft_single_quote(*(*matrix_command_line + i));
		*(*matrix_command_line + i) = set_origin(*(*matrix_command_line + i));
		i++;
	}
	return ;
}

void	expand_file(char **file_name, char **env, int n)
{
	(*file_name) = ft_double_quote(*file_name, env, n);
	(*file_name) = ft_single_quote(*file_name);
	(*file_name) = set_origin(*file_name);
	(*file_name) = set_redirection_to_origin(*file_name);
	return ;
}
