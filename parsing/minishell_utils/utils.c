/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:57:17 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/28 13:09:50 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_list	*creat_list_of_command_2(void)
{
	t_list *new_command_line;
	
	new_command_line = malloc(sizeof(t_list));
	if (!new_command_line)
		exit (EXIT_FAILURE);
	new_command_line->data = malloc(sizeof(t_data));
	if (!new_command_line->data)
		exit (EXIT_FAILURE);
	new_command_line->data->cmd = NULL;
	new_command_line->data->arguments = NULL;
	new_command_line->data->options = NULL;
	new_command_line->data->input_file = 0;
	new_command_line->data->output_file = 1;
	new_command_line->data->out_file_name = ft_strdup("stdout");
	new_command_line->data->in_file_name = ft_strdup("stdin");
	new_command_line->next = NULL;
	return (new_command_line);
}

char	*set_redirection_to_origin(char *arg)
{
	int i;

	if (!arg)
		return (arg);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == LESS_REDIRECTION)
			arg[i] = '<';
		else if (arg[i] == GREAT_REDIRECTION)
			arg[i] = '>';
		i++;
	}
	return (arg);
}

char	*set_origin(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (arg);
	while (arg[i])
	{
		if (arg[i] == PIPE_FLAG)
			arg[i] = PIPE_CHARACTER;
		else if (arg[i] == SPACE_FLAG)
			arg[i] = SPACE_CHARACTER;
		else if (arg[i] == OPTION_CHARACTER)
			arg[i] = '-';
		else if (arg[i] == SINGLE_QUOTE)
			arg[i] = '\'';
		else if (arg[i] == DOUBLE_QUOTE)
			arg[i] = '"';
		else if (arg[i] == EXPAND_CHARACTER)
			arg[i] = '$';
		i++;
	}
	return (arg);
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
