/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:51:37 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/21 19:02:47 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


int	take_in_files(t_list *list_command, char **matrix_command_line, int *j)
{
	int		i;
	char	**stock;
	int		index;
	int		len;
	char	*file_name;

	stock = ft_split(matrix_command_line[*j], '<');
	if (!*stock)
	{	
		(*j)++;
		stock = ft_split(matrix_command_line[*j], '>');
	}
	len = ft_strlen(matrix_command_line[*j]);
	i = -1;
	file_name = ft_strdup("\0");
	while (stock[++i])
	{
		index = search_index(matrix_command_line[*j], stock[i], len);
		if (index)
		{
			if (index > 1 && matrix_command_line[*j][index - 1] == '<'
				&& matrix_command_line[*j][index - 2] == '<')
			{
				free(file_name);
				file_name = ft_strdup("Heredoc");
				list_command->data->input_file = -1;
			}
			else
			{
				free(file_name);
				file_name = ft_strdup(get_file_name(stock[i], '>'));
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
		}
	}
	printf("\n\033[95m-------------------------------\033[00m\n");
	printf("in_file_name = %s\n", file_name);
	printf("input_file = %d\n", list_command->data->input_file);
	return (1);
}


void	*take_out_files(t_list *list_command, char **matrix_command_line, int *j)
{
	int		i;
	char	**stock;
	int		index;
	int		len;
	char	*file_name;
	int		count;

	count = search(matrix_command_line[*j], '>');
	stock = ft_split(matrix_command_line[*j], '>');
	if (!*stock)
	{	
		(*j)++;
		count = search(matrix_command_line[*j], '>');
		stock = ft_split(matrix_command_line[*j], '>');
	}
	len = ft_strlen(matrix_command_line[*j]);
	i = -1;
	file_name = ft_strdup("\0");
	while (stock[++i])
	{
		printf("i am hear\n");
		index = search_index(matrix_command_line[*j], stock[i], len);
		if (index)
		{
			if (index > 1 && matrix_command_line[*j][index - 1] == '>'
				&& matrix_command_line[*j][index - 2] == '>')
			{
				free(file_name);
				file_name = ft_strdup(get_file_name(stock[i], '<'));
				list_command->data->output_file 
					= open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			}
			else
			{
				free(file_name);
				file_name = ft_strdup(get_file_name(stock[i], '<'));
				list_command->data->output_file 
					= open(file_name, O_WRONLY | O_CREAT, 0644);
			}
		}
	}
	if (!stock[i] && i < count)
		printf("hope this is the cas i am looking for\n");
	printf("fd out = %d\n", list_command->data->output_file);
	return (file_name);
}

int	take_out_in_files(t_list *list_command, char **matrix_command_line)
{
	int	i;
	void	*out_file_name;
	int	in_file_name;
	
	out_file_name = NULL;
	i = -1;
	while (matrix_command_line[++i])
	{
		if (search(matrix_command_line[i], '<') || search(matrix_command_line[i], '>'))
		{
			in_file_name = take_in_files(list_command, matrix_command_line, &i);
			if (!in_file_name)
				return (0);
			out_file_name = take_out_files(list_command, matrix_command_line, &i);
			// if (!out_file_na
			// out_file_name = take_out_files(list_command, matrix_command_line[i]);
		}
	}
	printf("\n\033[95m-------------------------------\033[00m\n");
	if (out_file_name)
		printf("output_file_name = %s\n", out_file_name);
	printf("output_file = %d\n", list_command->data->output_file);

	
	// free(file_name);
	return (1);
}


// void	*take_out_files(t_list *list_command, char **matrix_command_line, int *j)
// {
// 	int		i;
// 	char	**stock;
// 	int		index;
// 	int		len;
// 	char	*file_name;
// 	int		count;
// 	count = search(matrix_command_line[*j], '>');
// 	stock = ft_split(matrix_command_line[*j], '>');
// 	// i = -1;
// 	// while (stock[++i])
// 	// 	printf("stock = '%s'\n", stock[i]);
// 	if (!*stock)
// 	{	
// 		(*j)++;
// 		count = search(matrix_command_line[*j], '>');
// 		stock = ft_split(matrix_command_line[*j], '>');
// 	}
// 	len = ft_strlen(matrix_command_line[*j]);
// 	i = -1;
// 	file_name = ft_strdup("\0");
// 	while (stock[++i])
// 	{
// 		index = search_index(matrix_command_line[*j], stock[i], len);
// 		printf("index = %d\n", index);
// 			if (index > 1 && matrix_command_line[*j][index - 1] == '>'
// 				&& matrix_command_line[*j][index - 2] == '>')
// 			{
// 				free(file_name);
// 				file_name = ft_strdup(get_file_name(stock[i], '<'));
// 				list_command->data->output_file 
// 					= open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 			}
// 			else
// 			{
// 				free(file_name);
// 				file_name = ft_strdup(get_file_name(stock[i], '<'));
// 				list_command->data->output_file 
// 					= open(file_name, O_WRONLY | O_CREAT, 0644);
// 			}
// 	}
// 	if (!stock[i] && i < count)
// 		printf("hope this is the cas i am looking for\n");
// 	return (file_name);
// }