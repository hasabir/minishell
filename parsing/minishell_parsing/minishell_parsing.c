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
	// char	*heredoc_file_name;
	t_list	*list_ptr;
	int		i;
	
	matrix_input = ft_split(input, '|');
	// heredoc_file_name = NULL;
	i = 0;
	list_ptr = *list_command;
	while (matrix_input[i])
	{
		// open_heredoc_files(*list_command, matrix_input[i]);
		if (!take_in_out_files(list_ptr, matrix_input[i], env))
			return (0);
		matrix_command_line = ft_split(matrix_input[i], ' ');
		if (!pars_command(matrix_command_line, &list_ptr, env))
			return (0);
		//if in file name = heredoc -> in_file_name = heredoc file name
		i++;
		if (matrix_input[i])
			ft_list_last(&list_ptr, creat_list_of_command_2());
	}
	return (1);
}
