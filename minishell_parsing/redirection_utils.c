/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:51:07 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/22 18:41:06 by hasabir          ###   ########.fr       */
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


char	**split_redirection(char **matrix_command_line, int **j, char c)
{
	char	**stock;
	int		count;

	count = search(matrix_command_line[**j], c);
	stock = ft_split(matrix_command_line[**j], c);
	if (!*stock)
	{	
		(**j)++;
		count = search(matrix_command_line[**j], c);
		stock = ft_split(matrix_command_line[**j], c);
	}
	return (stock);
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
		list_command->data->output_file 
			= open(file_name, O_WRONLY | O_CREAT, 0644);
		if (list_command->data->output_file == -1)
			return (NULL);
	}
	return (file_name);
}