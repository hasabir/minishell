/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:51:37 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/17 19:59:08 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_index(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 && s2[i] == 0)
		return (0);
	if (s1[i] == 0 && s2[i] == 0)
		return (0);
	// if (!*s2)
		// return ((char *)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (s1[i + j] && s2[j] && s2[j] == s1[i + j]
			&& i + j < len)
			j++;
		if (s2[j] == 0)
			return (i);
		i++;
	}
	return (0);
}

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

void	*take_out_files(t_list *list_command, char *matrix_command_line)
{
	int		i;
	char	**stock;
	int		index;
	int		len;
	char	*file_name;

	if (!search(matrix_command_line, '>'))
		return NULL;
	stock = ft_split(matrix_command_line, '>');
	len = ft_strlen(matrix_command_line);
	i = -1;
	file_name = ft_strdup("\0");
	while (stock[++i])
	{
		index = search_index(matrix_command_line, stock[i], len);
		if (index)
		{
			if (index > 1 && matrix_command_line[index - 1] == '>'
				&& matrix_command_line[index - 2] == '>')
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
	return (file_name);
}

void	*take_in_files(t_list *list_command, char *matrix_command_line)
{
	int		i;
	char	**stock;
	int		index;
	int		len;
	char	*file_name;

	if (!search(matrix_command_line, '<'))
		return NULL;
	stock = ft_split(matrix_command_line, '<');
	len = ft_strlen(matrix_command_line);
	i = -1;
	file_name = ft_strdup("\0");
	while (stock[++i])
	{
		index = search_index(matrix_command_line, stock[i], len);
		if (index)
		{
			if (index > 1 && matrix_command_line[index - 1] == '<'
				&& matrix_command_line[index - 2] == '<')
			{
				free(file_name);
				file_name = ft_strdup("Herdoc");
				list_command->data->input_file = -1;
			}
			else
			{
				free(file_name);
				file_name = ft_strdup(get_file_name(stock[i]));
				list_command->data->input_file
					= open(file_name, O_RDONLY);
				if (!list_command->data->input_file)
				{
					printf("in error\n");
					perror("NULL");
					return (NULL);
				}
			}
		}
	}
	return (file_name);
}

int	take_out_in_files(t_list *list_command, char **matrix_command_line)
{
	int	i;
	void	*out_file_name;
	void	*in_file_name;
	
	i = -1;
	while (matrix_command_line[++i])
	{
		if (search(matrix_command_line[i], '<') || search(matrix_command_line[i], '>'))
		{
			in_file_name = take_in_files(list_command, matrix_command_line[i]);
			if (!in_file_name)
				return (0);
			out_file_name = take_out_files(list_command, matrix_command_line[i]);
		}
	}
	printf("\n\033[95m-------------------------------\033[00m\n");
	printf("output_file_name = %s\n", out_file_name);
	printf("output_file = %d\n", list_command->data->output_file);
	printf("\n\033[95m-------------------------------\033[00m\n");

	printf("in_file_name = %s\n", in_file_name);
	printf("output_file = %d\n", list_command->data->input_file);
	
	// free(file_name);
	return (1);
}