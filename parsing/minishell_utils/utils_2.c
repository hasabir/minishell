/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:39:19 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/03 17:58:36 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	print_list_command(t_list *list_command)
{
	int	i;

	while (list_command)
	{
		printf("\n\033[95m-------------------------------\033[00m\n");
		// if (list_command->data->in_file_name)
			// printf("input_file_name = %s\n", list_command->data->in_file_name);
		printf("input_file = %d\n", list_command->data->input_file);
		printf("\n\033[95m-------------------------------\033[00m\n");
		// if (list_command->data->out_file_name)
		// 	printf("output_file_name = %s\n", list_command->data->out_file_name);
		printf("output_file = %d\n", list_command->data->output_file);	
		printf("\033[95m\n-------------------------------\033[00m\n");
		printf("cmd = %s\n", (list_command)->data->cmd);
		printf("\033[95m-------------------------------\033[00m\n");
		if (list_command->data->options)
		{
			i = -1;
			while (list_command->data->options[++i])
				printf("option = %s\n", list_command->data->options[i]);
		}
		printf("\033[95m-------------------------------\033[00m\n");
		if (list_command->data->arguments)
		{
			i = -1;
			while (list_command->data->arguments[++i])
				printf("argument = %s\n", list_command->data->arguments[i]);
		}
		list_command = list_command->next;
		printf("\033[91m\n*******************************************\033[00m\n");
	}
}

char	*ft_strstr(const char *s1, const char *s2)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	if (!s1 && s2[i] == 0)
		return (0);
	if (s1[i] == 0 && s2[i] == 0)
		return ("");
	if (s1)
		len = ft_strlen(s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (s1[i + j] && s2[j] && s2[j] == s1[i + j]
			&& i + j < len)
			j++;
		if (s2[j] == 0)
			return (((char *)s1) + i);
		i++;
	}
	return (0);
}

int	search_str(const char *s1, const char *s2)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	if (!s1 && s2[i] == 0)
		return (0);
	if (s1[i] == 0 && s2[i] == 0)
		return (0);
	if (s1)
		len = ft_strlen(s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (s1[i + j] && s2[j] && s2[j] == s1[i + j]
			&& i + j < len)
			j++;
		if (s2[j] == 0)
			return (1);
		i++;
	}
	return (0);
}

int	which_type_redirection(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>')
			return (1);
		if (str[i] == '<')
			return (0);
	}
	return (-1);
}

void	ft_get_str(char **matrix_command_line)
{
	char	**stock;

	if (which_type_redirection(*matrix_command_line) == 1)
		stock = ft_split(*matrix_command_line, '>');
	else
		stock = ft_split(*matrix_command_line, '<');
	free(*matrix_command_line);
	*matrix_command_line = ft_strdup(stock[0]);
	ft_free(stock);
}

int	search_characters(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
	{
		if (arg[i] == '|' || arg[i] == '"'|| arg[i] == '\''
			|| arg[i] == '>'|| arg[i] == '<'|| arg[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}
