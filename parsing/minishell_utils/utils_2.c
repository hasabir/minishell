/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:39:19 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/31 19:43:02 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	print_list_command(t_list *list_command)
{
	int	i;

	while (list_command)
	{
		printf("\n\033[95m-------------------------------\033[00m\n");
		if (list_command->data->in_file_name)
			printf("input_file_name = %s\n", list_command->data->in_file_name);
		printf("input_file = %d\n", list_command->data->input_file);
		printf("\n\033[95m-------------------------------\033[00m\n");
		if (list_command->data->out_file_name)
			printf("output_file_name = %s\n", list_command->data->out_file_name);
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

int search(char *str, char c)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

char	*search_env(char **env, char *to_find, char **tmp)
{
	int		j;
	char	*str;
	int		i;
	int		n;

	i = 0;
	str = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && to_find[j] && env[i][j] == to_find[j])
			j++;
		if (env[i][j] == '=')
		{
			n = -1;
			while (++n < j && tmp && *tmp)
				(*tmp)++;
			str = env[i];
			j++;
			return (str + j);
		}
		i++;
	}
	return (0);
}

int ft_error(int n, char option, char *str_option)
{
	if (option && !str_option)
		printf("Petit_shell: syntax error near unexpected token `%c'\n", option);
	else if (str_option && !option)
		printf("Petit_shell: syntax error near unexpected token `%s'\n", str_option);
	else
	{
		if (n == 0)
			printf("Petit_shell: syntax error near unexpected token `%c'\n", option);
		else if (n == 1)
			printf("Petit_shell: syntax error near unexpected token `%s'\n", str_option);
	}
	return (-1);
}

void	ft_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free (str);
}
