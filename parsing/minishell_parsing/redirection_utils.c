/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:51:07 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/27 22:32:06 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../minishell.h"
#include "../parsing.h"

char	*get_file_name(char	*str, char c)
{
	int		i;
	int		len;
	char	*file_name;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	file_name = malloc(sizeof(char) * (len + 1));
	i = -1;
	while (++i < len)
		file_name[i] = str[i];
	file_name[i] = '\0';
	return (file_name);
}

int	split_in_redirection(char ***stock, char **matrix_command_line, int **j, int flag)
{
	int		count_redirect;
	int		is_end;
	if (!matrix_command_line[**j])
		return (-1);
	is_end = ft_strncmp(ft_strrchr(matrix_command_line[**j], '<'), "<",
		ft_strlen(matrix_command_line[**j]));
	*stock = ft_split(matrix_command_line[**j], '<');	
	count_redirect = search(matrix_command_line[**j], '<');
	if (matrix_command_line[**j]
		&& ((is_end == 0 && count_redirect == 1 && flag == 1)
		|| count_redirect != 1 ))
	{
		if ((matrix_command_line[(**j) + 1] && matrix_command_line[(**j) + 1][0] == '>'))
			return (1);
		return (0);
	}
	if (!*stock || (is_end == 0 && count_redirect == 1))
	{	
		ft_free(*stock);
		(**j)++;
		*stock = ft_split(matrix_command_line[**j], '<');
	}
	return (1);
}

int	split_out_redirection(char ***stock, char **matrix_command_line, int **j, int flag)
{
	int		count_redirect;
	int		is_end;

	if (!matrix_command_line[**j])
		return (-1);
	is_end = ft_strncmp(ft_strrchr(matrix_command_line[**j], '>'), ">",
		ft_strlen(matrix_command_line[**j]));
	*stock = ft_split(matrix_command_line[**j], '>');	
	count_redirect = search(matrix_command_line[**j], '>');
	if (matrix_command_line[**j]
		&& ((is_end == 0 && count_redirect == 1 && flag == 1) || count_redirect != 1))
	{
		if ((matrix_command_line[(**j) + 1] && matrix_command_line[(**j) + 1][0] == '>'))
			return (1);
		return (0);
	}
	if (!*stock || (is_end == 0 && count_redirect == 1))
	{	
		ft_free(*stock);
		(**j)++;
		*stock = ft_split(matrix_command_line[**j], '>');
	}
	return (1);
}

char	*open_in_files(t_list *list_command ,char *matrix_command_line, char *stock, int index)
{
	char	*file_name;

	file_name = ft_strdup("\0");
	if (index > 1 && matrix_command_line[index - 1] == '<'
		&& matrix_command_line[index - 2] == '<')
	{
		free(file_name);
		file_name = ft_strdup("Heredoc");
		list_command->data->input_file = -1;
	}
	else
	{
		free(file_name);
		file_name = ft_strdup(get_file_name(stock, '>'));
		list_command->data->input_file
			= open(file_name, O_RDONLY);
		if (list_command->data->input_file == -1)
		{
			write(1, "Petit_shell: ", 14);
			write(1, file_name, ft_strlen(file_name));
			perror(" ");
			return (0);
		}
	}
	return (file_name);
}

char	*open_out_files(t_list *list_command ,char *matrix_command_line, char *stock, int index)
{
	char	*file_name;

	file_name = ft_strdup("\0");
	if (index > 1 && matrix_command_line[index - 1] == '>'
		&& matrix_command_line[index - 2] == '>')
	{
		free(file_name);
		file_name = ft_strdup(get_file_name(stock, '<'));
		list_command->data->output_file 
			= open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (list_command->data->output_file == -1)
			return (NULL);
	}
	else
	{
		free(file_name);
		file_name = ft_strdup(get_file_name(stock, '<'));
		if (*file_name)
			list_command->data->output_file 
				= open(file_name, O_WRONLY | O_CREAT, 0644);
		if (list_command->data->output_file == -1)
		{
			free (file_name);
			perror(NULL);
			return (NULL);
		}
	}
	return (file_name);
}