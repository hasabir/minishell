/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:19:08 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/07 18:39:57 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*eliminate_quote(char *cmd)
{
	int	i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	while(cmd[i])
	{
		if (cmd[i] == DOUBLE_QUOTE && s != 1)
		{
			if (d == 0)
				d++;
			else if (d == 1)
				d = 0;
			// printf("-d-- \n");
		}
		if (cmd[i] == SINGLE_QUOTE && d!= 1)
		{
			if (s == 0)
				s++;
			else if (s == 1)
				s = 0;
			// printf("s*** \n");
		}
		i++;
	}
	return (cmd);
}

void	pars_command(char **matrix_command_line, t_list **list_command)
{
	int j;

	j = 0;

	/*
		while -> check if there is LESS or GREAT
	*/
	eliminate_quote(matrix_command_line[j]);
	(*list_command)->data->cmd = set_command(matrix_command_line[j]);
	printf("cmd = %s\n", (*list_command)->data->cmd);
	j++;
	// (*list_command)->data->options = set_options(matrix_command_line[j]);
	
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
		printf("matrix_input = %s\n", matrix_input[i]);
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