/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:37:26 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/12 19:48:58 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	exit_case(void)
{
	global.exit_status = 1;
	global.is_heredoc = -2;
	write (1, ">\n", 2);
}

int	unlink_heredoc_file(char *input_ptr, char *heredoc_file_name)
{
	if ((input_ptr && *input_ptr) || global.is_heredoc == -2)
	{
		if (unlink(heredoc_file_name) == -1)
		{
			ft_perror(heredoc_file_name, 2);
			return (0);
		}
		if (global.is_heredoc == -2)
			return (0);
	}
	return (1);
}
