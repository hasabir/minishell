/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:57:17 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/08 12:05:58 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void creat_list_of_command(t_list **command_line)
{
	t_list *new_command_line;

	new_command_line = malloc(sizeof(t_list));
	new_command_line->data = malloc(sizeof(t_data));
	new_command_line->data->cmd = NULL;
	new_command_line->data->arguments = NULL;
	new_command_line->data->options = NULL;
	new_command_line->data->input_file = DEFAULT_INPUT;
	new_command_line->data->output_file = DEFAULT_OUTPUT;
	new_command_line->next = NULL;
	*command_line = ft_list_last(*command_line);
	*command_line = new_command_line;
	return ;
}

void	set_origin(char **arg)
{
	int	i;

	i = 0;
	while (*arg[i])
	{
		if (*arg[i] == PIPE_FLAG)
			*arg[i] = PIPE_CHARACTER;
		else if (*arg[i] == SPACE_FLAG)
			*arg[i] = SPACE_CHARACTER;
		else if (*arg[i] == LESS_REDIRECTION)
			*arg[i] = '<';
		else if (*arg[i] == GREAT_REDIRECTION)
			*arg[i] = '>';
		else if (*arg[i] == OPTION_CHARACTER)
			*arg[i] = '-';
		else if (*arg[i] == SINGLE_QUOTE)
			*arg[i] = '\'';
		else if (*arg[i] == DOUBLE_QUOTE)
			*arg[i] = '"';
		i++;
	}
	return ;
}

int which_type_quote(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"')
			return (2);
		if (cmd[i] == '\'')
			return (1);
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
