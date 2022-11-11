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

char	**open_heredoc_matrix(char ***matrix_input, char **env)
{
	int		i;
	char	*heredoc;
	int		len;
	char	**heredoc_matrix;

	len = -1;
	while (matrix_input[++len]);
	heredoc_matrix = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (*(*matrix_input + i))
	{
		heredoc = open_heredoc_files(*(*matrix_input + i), i, env);
		if (!heredoc)
			heredoc_matrix[i] = ft_strdup("");
		else
			heredoc_matrix[i] = ft_strdup(heredoc);
		i++;
	}
	heredoc_matrix[i] = NULL;
	return(heredoc_matrix);
}

int	pars_command(char **matrix_command_line, t_list **list_command, char **env)
{
	int	j;

	j = 0;
	set_arg(&matrix_command_line, env);
	if (!*matrix_command_line)
	{
		(*list_command)->data->cmd = ft_strdup("");
		ft_free(matrix_command_line);
		return (0);
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
	matrix_command_line = ft_split(*input, ' ');
	if (!pars_command(matrix_command_line, &list_ptr, env))
		return (0);
	free(matrix_command_line);
	matrix_command_line = NULL;
	if (list_ptr->data->input_file == -1)
	{
		// printf("heredoc = %")
		list_ptr->data->input_file = open(heredoc, O_RDONLY);
	}
	if (*heredoc)
	{
		if (unlink(heredoc) == -1)
			return (ft_perror(heredoc, 2));
	}
	return (1);
}

int	parsing(char *input, t_list	**list_command, char **env)
{
	char	**matrix_input;
	t_list	*list_ptr;
	char	**heredoc_matrix;
	int		i;

	i = 0;
	matrix_input = ft_split(input, '|');
	heredoc_matrix = open_heredoc_matrix(&matrix_input, env);
	list_ptr = *list_command;
	while (matrix_input[i])
	{
		if (take_in_out_files(list_ptr, matrix_input[i], env))
			pars_matrix_input(list_ptr, &matrix_input[i], heredoc_matrix[i], env);
		free(matrix_input[i]);
		if (matrix_input[++i])
			ft_list_last(&list_ptr, creat_list_of_command());
	}
	ft_free(heredoc_matrix);
	free(matrix_input);
	matrix_input = NULL;
	return (1);
}

// int	parsing(char *input, t_list	**list_command, char **env)
// {
// 	char	**matrix_input;
// 	char	*heredoc;
// 	t_list	*list_ptr;
// 	int		i;

// 	i = 0;
// 	matrix_input = ft_split(input, '|');
// 	list_ptr = *list_command;
// 	while (matrix_input[i])
// 	{
// 		heredoc = open_heredoc_files(matrix_input[i], i, env);
// 		printf("matrix input = %s\n", matrix_input[i]);
// 		if (take_in_out_files(list_ptr, matrix_input[i], env))
// 			pars_matrix_input(list_ptr, &matrix_input[i], heredoc, env);
// 		free(matrix_input[i]);
// 		if (matrix_input[++i])
// 			ft_list_last(&list_ptr, creat_list_of_command());
// 		free(heredoc);
// 		heredoc = NULL;
// 	}
// 	free(matrix_input);
// 	matrix_input = NULL;
// 	return (1);
// }
