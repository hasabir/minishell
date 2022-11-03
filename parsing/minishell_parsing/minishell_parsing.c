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
	take_cmd((*list_command), matrix_command_line, &j);
	take_options((*list_command), matrix_command_line, &j);
	take_argument((*list_command), matrix_command_line, &j);
	return (1);
}

int	parsing(char *input, t_list	**list_command, char **env)
{
	char	**matrix_input;
	char	**matrix_command_line;
	int		heredoc_fd;
	t_list	*list_ptr;
	int		i;

	matrix_input = ft_split(input, '|');
	i = 0;
	list_ptr = *list_command;
	while (matrix_input[i])
	{
		heredoc_fd = open_heredoc_files(matrix_input[i], i, env);
		if (!take_in_out_files(list_ptr, matrix_input[i], env))
			return (0);
		matrix_command_line = ft_split(matrix_input[i], ' ');
		free(matrix_input[i]);
		if (!pars_command(matrix_command_line, &list_ptr, env))
			return (0);
		printf("heredoc_fd = %d\n", heredoc_fd);
		if (list_ptr->data->input_file == -1)
			list_ptr->data->input_file = heredoc_fd;
		i++;
		if (matrix_input[i])
			ft_list_last(&list_ptr, creat_list_of_command_2());
		free(matrix_command_line);
		matrix_command_line = NULL;
	}
	free(matrix_input);
	matrix_input = NULL;
	return (1);
}
