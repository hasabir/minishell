/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:19:08 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/08 11:55:02 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_command(char **matrix_command_line, t_list **list_command)
{
	int j;
	int i;

	j = 0;
	/*
		while -> check if there is LESS or GREAT
	*/
	i = -1;
	while (matrix_command_line[++i])
		printf("command_line[i]= %s\n\n", matrix_command_line[i]);


	
	(*list_command)->data->cmd = set_command(matrix_command_line[j]);
	printf("cmd = %s\n", (*list_command)->data->cmd);
	i = 0;
	while (matrix_command_line[++j])
	{	
		matrix_command_line[j] = set_command(matrix_command_line[j]);
		if (matrix_command_line[j][0] == OPTION_CHARACTER
			|| matrix_command_line[j][0] == '-')
		{
			(*list_command)->data->options[i]
				= ft_strjoin((*list_command)->data->options[i], matrix_command_line[j]);
			i++;
		}
		else
		{
			(*list_command)->data->options[i] = NULL;
			break;
		}
		j++;
	}
	printf("option = %s\n", (*list_command)->data->options);
	return;
}



t_list	*parsing(char *input, t_list	*list_command)
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
		pars_command(matrix_command_line, &list_command);
		i++;
	}
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