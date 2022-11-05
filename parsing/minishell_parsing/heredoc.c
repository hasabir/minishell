/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 10:18:28 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/05 18:58:43 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

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
}

int	read_from_heredoc(int heredoc_fd, char *delimiter, char **env, int n)
{
	char	*input;
	char	*line;

	line = NULL;
	input = readline(">");
	(void)env;
	while (!*input || ft_strncmp(input , delimiter, ft_strlen(input)))
	{
		if (n == 0 && search(input , '$'))
			input = expand(input, env);
		line = ft_strjoin(input, "\n");
		free(input);
		ft_putstr_fd(line, heredoc_fd);
		input = readline(">");
	}
	free(input);
	return (0);
}

char	*open_heredoc(char *delimeter, char *heredoc_file_name, char **env, int n)
{
	char	*heredoc;
	int		heredoc_fd;

	heredoc = ft_strjoin("/tmp/" ,heredoc_file_name);
	free(heredoc_file_name);
	heredoc_fd =
		open(heredoc, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (heredoc_fd == -1)
	{
		perror(NULL);
		return (NULL);
	}
	read_from_heredoc(heredoc_fd, delimeter, env, n);
	return (heredoc);
}

char	*open_heredoc_files(char *input, int c,char **env)
{
	char	*input_ptr;
	char	*delimiter;
	char	*heredoc_file_name;
	int		heredoc_fd;
	int		n;

	if (!search_str(input, "<<"))
		return (0);
	input_ptr = input;
	heredoc_file_name = NULL;
	delimiter = NULL;
	heredoc_fd = 0;
	n = 0;
	input_ptr = ft_strstr(input_ptr, "<<");
	while (input_ptr && *input_ptr)
	{
		while(*input_ptr && (*input_ptr == '<' || is_space(*input_ptr)))
			input_ptr++;
		heredoc_file_name = get_file_name(input_ptr);
		if (search(heredoc_file_name, '"') || search(heredoc_file_name, '\''))
			n = 1;
		expand_file(&heredoc_file_name, env, 0);
		free(delimiter);
		delimiter = ft_strdup(heredoc_file_name);
		get_heredoc_name(&heredoc_file_name, c);
		heredoc_file_name = open_heredoc(delimiter, heredoc_file_name, env, n);
		input_ptr = ft_strstr(input_ptr, "<<");
	}
	free(delimiter);
	return (heredoc_file_name);
}

