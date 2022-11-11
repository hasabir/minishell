/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:35:16 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/11 18:09:35 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	open_file(t_list *list_command, char *in_file_name)
{
	list_command->data->input_file = 0;
	if (open(in_file_name, O_RDWR | O_TRUNC | O_CREAT, 0644) == -1)
		return(ft_perror(in_file_name, 1));
	return (1);
}

