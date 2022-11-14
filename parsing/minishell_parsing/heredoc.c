/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 10:18:28 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/14 22:25:13 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	read_from_heredoc(int heredoc_fd, char *delimiter, char **env, int n)
{
	char	*input;
	char	*line;

	signal(SIGINT, SIG_DFL);
	line = NULL;
	input = readline(">");
	g_global.is_heredoc = -1;
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
	exit (0);
}

char	*open_heredoc(char *delimeter, char *heredoc_name, char **env, int n)
{
	char		*heredoc;
	int			heredoc_fd;
	pid_t		id;
	int			status;

	heredoc = ft_strjoin("/tmp/.", heredoc_name);
	free(heredoc_name);
	heredoc_fd
		= open(heredoc, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (heredoc_fd == -1)
		return (error(NULL));
	id = fork();
	if (id == -1)
		return (error(NULL));
	signal(SIGINT, SIG_IGN);
	if (id == 0)
		read_from_heredoc(heredoc_fd, delimeter, env, n);
	waitpid(id, &status, 0);
	if (WIFSIGNALED(status))
		exit_case(heredoc, delimeter);
	signal(SIGINT, handle_signals);
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
		if (!unlink_heredoc_file(input_ptr, heredoc_file_name, 0))
			return (NULL);
	}
	free(delimiter);
	return (heredoc_file_name);
}

char	**open_heredoc_matrix(char *input, char ***matrix_input, char **env)
{
	int		i;
	char	*heredoc;
	int		len;
	char	**heredoc_matrix;

	*matrix_input = ft_split(input, '|');
	len = 0;
	while (matrix_input[0][len])
		len++;
	heredoc_matrix = (char **)malloc(sizeof(char *) * (len + 1));
	if (!heredoc_matrix)
		malloc_failed();
	i = -1;
	while (matrix_input[0][++i])
	{
		heredoc = open_heredoc_files(matrix_input[0][i], i, env);
		if (g_global.is_heredoc == -2 || i == 16)
			break ;
		if (!heredoc)
			heredoc_matrix[i] = ft_strdup("NO");
		else
			heredoc_matrix[i] = heredoc;
	}
	heredoc_matrix[i] = NULL;
	return (free_heredoc(heredoc_matrix));
}
