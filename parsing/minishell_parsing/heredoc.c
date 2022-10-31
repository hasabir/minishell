/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 10:18:28 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/29 18:36:40 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

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

void	get_heredoc_name(char **heredoc_file_name)
{
	char	**stock;

	stock = ft_split(ttyname(1), '/');
	*heredoc_file_name = ft_strjoin(*heredoc_file_name, stock[1]);
}

int	open_heredoc(char *delimeter, char *heredoc_file_name)
{
	// int fd;
	(void)delimeter;
	heredoc_file_name = ft_strjoin("/tmp/" ,heredoc_file_name);
	// fd = open(heredoc_file_name, )
	if (open("/tmp/file6", O_CREAT | O_RDWR , 0600) == -1)
		perror(NULL);
	return (0);
}

char	*open_heredoc_files(t_list *list_command, char *matrix_input)
{
	char	*matrix_input_ptr;
	char	*delimiter;
	char	*heredoc_file_name;

	if (!search_str(matrix_input, "<<"))
		return (0);
	matrix_input_ptr = matrix_input;
	heredoc_file_name = NULL;
	delimiter = NULL;
	// while (*matrix_input_ptr)
	// {
		matrix_input_ptr = ft_strstr(matrix_input, "<<");
		printf("matrix_input = %s\n", matrix_input_ptr);
		matrix_input_ptr++;
		matrix_input_ptr++;
		if (matrix_input_ptr)
		{
			heredoc_file_name = get_file_name(matrix_input_ptr);
			delimiter = ft_strdup(heredoc_file_name);
		}
		else
			return (heredoc_file_name);
		get_heredoc_name(&heredoc_file_name);
		open_heredoc(delimiter, heredoc_file_name);
		// matrix_input_ptr++;
	// }
	printf("tty name = %s\n", ttyname(0));
	(void)list_command ;
	return (0);
}























