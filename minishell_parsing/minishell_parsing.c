/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:19:08 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/21 19:03:39 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	pars_command(char **matrix_command_line, t_list *list_command, char **env)
{
	int	j;
	
	j = 0;
	if (!take_out_in_files(list_command, matrix_command_line))
		return (0);
	set_arg(&matrix_command_line, env);
	take_cmd(list_command, matrix_command_line, &j);
	take_options(list_command, matrix_command_line, &j);
	take_argument(list_command, matrix_command_line, &j);
	ft_free(matrix_command_line);
	(void)env;
	return (1);
}

t_list	*parsing(char *input, t_list	*list_command, char **env)
{
	printf("\033[91mI am parsing : \033[00m%s\n\n", input);
	char	**matrix_input;
	char	**matrix_command_line;
	int		i;
	
	matrix_input = ft_split(input, '|');
	i = 0;
	while (matrix_input[i])
	{
		creat_list_of_command(&list_command);
		matrix_command_line = ft_split(matrix_input[i], ' ');
		int j = -1;
		while (matrix_command_line[++j])
			printf("\033[02mmatrix[%d] = %s\033[00m\n",j, matrix_command_line[j]);
		if (!pars_command(matrix_command_line, list_command, env))
			return (NULL);
		free (matrix_input[i]);
		i++;
		printf("\033[91m\n*******************************************\033[00m\n");
	}
	free(matrix_input);
	return (list_command);
}
