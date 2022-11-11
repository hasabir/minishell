/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 10:18:28 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/11 23:34:44 by hasabir          ###   ########.fr       */
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
	return ;
}



int	read_from_heredoc(int heredoc_fd, char *delimiter, char **env, int n)
{
	char	*input;
	char	*line;

	line = NULL;
	input = readline(">");
	while (input && (!*input || ft_strcmp(input, delimiter)))
	{
		if ((!delimiter || !*delimiter) && !*input)
			break ;
		if (n == 0 && search(input, '$'))
			input = expand(input, env);
		line = ft_strjoin(input, "\n");
		ft_putstr_fd(line, heredoc_fd);
		free(input);
		free(line);
		input = readline(">");
	}
	if (input == NULL)
		exit (0);
	free(input);
	exit (1);
}

char	*open_heredoc(char *delimeter, char *heredoc_name, char **env, int n)
{
	char		*heredoc;
	int			heredoc_fd;
	pid_t		id;

	heredoc = ft_strjoin("/tmp/.", heredoc_name);
	free(heredoc_name);
	heredoc_fd
		= open(heredoc, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (heredoc_fd == -1)
	{
		perror(NULL);
		return (NULL);
	}
	id = fork();
	if (id == -1)
	{
		perror(NULL);
		return (NULL);
	}
	// signal(SIGINT, handle_signals);
	if (id == 0)
	{
		// signal(SIGINT, handle_signals);
		// kill(0, SIGINT);
		read_from_heredoc(heredoc_fd, delimeter, env, n);
	}
	else
	{
		wait(NULL);
	}
	return (heredoc);
}

char	*heredoc_file(char **input_ptr, char **delimiter, char **env, int c)
{
	int		n;
	char	*heredoc_file_name;

	n = 0;
	while (**input_ptr && (**input_ptr == '<' || is_space(**input_ptr)))
		(*input_ptr)++;
	heredoc_file_name = get_file_name(*input_ptr);
	if (search(heredoc_file_name, '"') || search(heredoc_file_name, '\''))
		n = 1;
	expand_file(&heredoc_file_name, env, 0);
	free(*delimiter);
	*delimiter = ft_strdup(heredoc_file_name);
	get_heredoc_name(&heredoc_file_name, c);
	heredoc_file_name = open_heredoc(*delimiter, heredoc_file_name, env, n);
	return (heredoc_file_name);
}

char	*open_heredoc_files(char *input, int c, char **env)
{
	char	*input_ptr;
	char	*delimiter;
	char	*heredoc_file_name;

	if (!search_str(input, "<<"))
		return (0);
	input_ptr = input;
	delimiter = NULL;
	heredoc_file_name = NULL;
	input_ptr = ft_strstr(input_ptr, "<<");
	while (input_ptr && *input_ptr)
	{
		free(heredoc_file_name);
		heredoc_file_name = heredoc_file(&input_ptr, &delimiter, env, c);
		input_ptr = ft_strstr(input_ptr, "<<");
		if (input_ptr && *input_ptr)
		{
			if (unlink(heredoc_file_name) == -1)
			{
				ft_perror(heredoc_file_name, 2);
				return (NULL);
			}
		}
	}
	free(delimiter);
	return (heredoc_file_name);
}
