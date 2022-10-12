/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:19:08 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/10 19:04:39 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_command(char **matrix_command_line, t_list **list_command, char **env)
{
	int j;
	
	j = 0;
	set_arg(&matrix_command_line, env);
	take_cmd(list_command, matrix_command_line, &j);
	take_options(list_command, matrix_command_line, &j);
	take_argument(list_command, matrix_command_line, &j);
	ft_free(matrix_command_line);

	return ;
}

t_list	*parsing(char *input, t_list	*list_command, char **env)
{
	printf("\033[91mI am parsing : \033[00m%s\n\n", input);
	char **matrix_input;
	char **matrix_command_line;
	int i;
	
	matrix_input = ft_split(input, '|');
	i = 0;
	while (matrix_input[i])
	{
		creat_list_of_command(&list_command);
		matrix_command_line = ft_split(matrix_input[i], ' ');
		pars_command(matrix_command_line, &list_command, env);
		free (matrix_input[i]);
		i++;
		printf("\n|||||||||||||||||||||||||||||||||||||||||||\n");
	}
	free(matrix_input);
	return (list_command);
}

/*

les cas :
	if (< > << >>)
		* what comes next is a file

	if (|)
		i need to creat an other node *done*

	if ("" or '')
		i don't have to take the quoests with me
	if ("")
		i need to expand?


*/