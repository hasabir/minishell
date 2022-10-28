/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:51:07 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/28 12:25:54 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*get_file_name(char	*str)
{
	int		i;
	int		len;
	char	*file_name;

	len = 0;
	while (str[len] && str[len] != '>'
		&& str[len] != '<' && !is_space(str[len]))
		len++;
	file_name = malloc(sizeof(char) * (len + 1));
	i = -1;
	while (++i < len)
	{
		file_name[i] = *str;
		str++;
	}
	file_name[i] = '\0';
	return (file_name);
}

int	open_out_file(t_list *list_command, char *matrix_input, int out_type)
{
	if (out_type == 1)
	{
		free(list_command->data->out_file_name);
		list_command->data->out_file_name = get_file_name(matrix_input);
		list_command->data->output_file =
			open(list_command->data->out_file_name,
				O_WRONLY | O_CREAT, 0644);
		if (list_command->data->output_file == -1)
			return (0);
	}
	else
	{
		free(list_command->data->out_file_name);
		list_command->data->out_file_name = get_file_name(matrix_input);
		list_command->data->output_file =
			open(list_command->data->out_file_name,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (list_command->data->output_file == -1)
			return (0);
	}
	return (1);
}

int	open_in_file(t_list *list_command, char *matrix_input, int in_type)
{
	if (in_type == 1)
	{
		free(list_command->data->in_file_name);
		list_command->data->in_file_name = get_file_name(matrix_input);
		list_command->data->input_file =
			open(list_command->data->in_file_name, O_RDONLY);
		if (list_command->data->input_file == -1)
		{
			write(1, "Petit_shell: ", 14);
			write(1, list_command->data->in_file_name,
				ft_strlen(list_command->data->in_file_name));
			perror(" ");
			return (0);
		}
	}
	else
	{
		free(list_command->data->out_file_name);
		list_command->data->in_file_name = ft_strdup("Heredoc");
		list_command->data->input_file = -1;
	}
	return (1);
}