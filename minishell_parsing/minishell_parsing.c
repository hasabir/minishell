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

#include "../minishell.h"



int	pars_command(char **matrix_command_line, t_list **list_command, char **env)
{
	int	j;
	
	j = 0;
	if (!take_out_in_files((*list_command), matrix_command_line))
		return (0);
	set_arg(&matrix_command_line, env);
	take_cmd((*list_command), matrix_command_line, &j);
	take_options((*list_command), matrix_command_line, &j);
	take_argument((*list_command), matrix_command_line, &j);
	// ft_free(matrix_command_line);
	// (void)env;
	return (1);
}

void	parsing(char *input, t_list	**list_command, char **env)
{
	printf("\033[91mI am parsing : \033[00m%s\n\n", input);
	char	**matrix_input;
	char	**matrix_command_line;
	t_list	*list_ptr;
	int		i;
	
	matrix_input = ft_split(input, '|');
	i = 0;
	list_ptr = *list_command;
	while (matrix_input[i])
	{
		
		matrix_command_line = ft_split(matrix_input[i], ' ');
		if (!pars_command(matrix_command_line, &list_ptr, env))
			return ;
		i++;
		if (matrix_input[i])
			ft_list_last(&list_ptr, creat_list_of_command_2());
		printf("\033[91m\n*******************************************\033[00m\n");
	}
	return ;
}
