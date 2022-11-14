/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:37:26 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/14 15:49:20 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	exit_case(char *heredoc_file_name, char *delimiter)
{
	g_global.exit_status = 1;
	g_global.is_heredoc = -2;
	write (1, ">\n", 2);
	free(heredoc_file_name);
	free(delimiter);
}

int	unlink_heredoc_file(char *input_ptr, char *heredoc_file_name, int flag)
{
	if (flag == 1)
	{
		if (ft_strcmp(heredoc_file_name, "NO"))
		{
			if (unlink(heredoc_file_name) == -1)
				return (-1);
		}
	}
	if (!flag)
	{
		if ((input_ptr && *input_ptr) || g_global.is_heredoc == -2)
		{
			if (g_global.is_heredoc == -2)
				return (0);
		}
	}
	return (1);
}

void	get_heredoc_name(char **heredoc_file_name, int c)
{
	char	*tmp;
	char	*stock;

	tmp = ft_strjoin(*heredoc_file_name, ft_strstr(ttyname(1), "tty"));
	free(*heredoc_file_name);
	*heredoc_file_name = NULL;
	stock = ft_itoa(c);
	*heredoc_file_name = ft_strjoin(tmp, stock);
	free(stock);
	free(tmp);
	return ;
}

char	**free_heredoc(char **heredoc_matrix)
{
	if (g_global.is_heredoc == -2)
	{
		if (*heredoc_matrix)
			ft_free(heredoc_matrix);
		else
			free(heredoc_matrix);
		return (NULL);
	}
	return (heredoc_matrix);
}
