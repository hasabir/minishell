/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:19:08 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/23 12:34: by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	pars_command(char **matrix_command_line, t_list **list_command, char **env)
{
	int	j;

	j = 0;
	set_arg(&matrix_command_line, env);
	if (!*matrix_command_line)
	{
		(*list_command)->data->cmd = ft_strdup("");
		free(*matrix_command_line);
		return (1);
	}
	take_cmd((*list_command), matrix_command_line, &j);
	take_options((*list_command), matrix_command_line, &j);
	take_argument((*list_command), matrix_command_line, &j);
	return (1);
}

int	pars_matrix_input(t_list *list_ptr, char **input, char *heredoc, char **env)
{
	char	**matrix_command_line;

	*input = ft_double_quote(*input, env, 1);
	if (*input && !**input)
		return (0);
	if (!*input)
	{
		list_ptr->data->cmd = ft_strdup("");
		free(*input);
		return (1);
	}
	matrix_command_line = ft_split(*input, ' ');
	if (!pars_command(matrix_command_line, &list_ptr, env))
		return (0);
	free(matrix_command_line);
	matrix_command_line = NULL;
	if (list_ptr->data->input_file == -1)
	{
		list_ptr->data->input_file = open(heredoc, O_RDONLY);
		if (list_ptr->data->input_file == -1)
			return (ft_perror(heredoc, 2));
	}
	return (1);
}

int	parsing(char *input, t_list	**list_command, char **env)
{
	char	**matrix;
	t_list	*list_ptr;
	char	**heredoc;
	int		i;
	int		return_value;

	i = 0;
	return_value = 1;
	heredoc = open_heredoc_matrix(input, &matrix, env);
	if (g_global.is_heredoc == -2)
		return (ft_free(matrix));
	list_ptr = *list_command;
	while (return_value && matrix[i])
	{
		if (take_in_out_files(list_ptr, matrix[i], env))
		{
			if (!pars_matrix_input(list_ptr, &matrix[i], heredoc[i], env))
				return_value = 0;
		}
		if (matrix[++i])
			ft_list_last(&list_ptr, creat_list_of_command());
	}
	ft_free(heredoc);
	ft_free(matrix);
	return (return_value);
}
