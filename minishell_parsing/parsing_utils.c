/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:51:50 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/16 17:05:30 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	take_cmd(t_list *list_command, char **matrix_command_line, int *j)
{
	printf("\n");
	printf("\033[95m-------------------------------\033[00m\n");
	(list_command)->data->cmd = matrix_command_line[*j];
	printf("cmd = %s\n", (list_command)->data->cmd);
	printf("\033[95m-------------------------------\033[00m\n");
	return ;
}

void	take_argument(t_list *list_command, char **matrix_command_line, int *j)
{
	int	i;

	i = 0;
	while (matrix_command_line[*j]
		&& (matrix_command_line[*j][0] != '<'
		|| matrix_command_line[*j][0] != '>'))
	{
		if (i != 0)
			(list_command)->data->arguments = ft_strjoin((list_command)->data->arguments, " ");
		(list_command)->data->arguments = ft_strjoin((list_command)->data->arguments,
			matrix_command_line[*j]);
		i++;
		(*j)++;
	}
	printf("argument = %s\n", (list_command)->data->arguments);
	return ;
}

void	take_options(t_list *list_command, char **matrix_command_line, int *j)
{
	int i;

	i = 0;
	*j += 1;
	while (matrix_command_line[*j])
	{	
		if (!(list_command)->data->options)
			(list_command)->data->options = malloc(sizeof(char *));
		if (search_characters(matrix_command_line[*j]) == 1
			&& matrix_command_line[*j][0] == '-')
		{
			(list_command)->data->options[i]
				= ft_strdup(matrix_command_line[*j]);
			printf("option = %s\n", (list_command)->data->options[i]);
			i++;
		}
		else
		{
			(list_command)->data->options[i] = NULL;
			printf("option = %s\n", list_command->data->options[i]);
			break ;
		}
		(*j)++;
	}
	printf("\033[95m-------------------------------\033[00m\n");
	return ;
}

void	set_arg(char ***matrix_command_line, char **env)
{
	int i;

	i = 0;
	while (*(*matrix_command_line + i))
	{
		*(*matrix_command_line + i) = ft_double_quote(*(*matrix_command_line + i), env);
		*(*matrix_command_line + i) = ft_single_quote(*(*matrix_command_line + i));
		*(*matrix_command_line + i) = set_origin(*(*matrix_command_line + i));
		i++;
	}
	return ;
}


// void	take_out_in_files(t_list *list_command, char **matrix_command_line)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (matrix_command_line[++i])
// 	{
// 		if (search(matrix_command_line[i], '<') || search(matrix_command_line[i], '>'))
// 		{
// 			take_out_file(list_command, matrix_command_line[i]);
// 		}
// 	}
// 	return ;
// }