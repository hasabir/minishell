/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:59:46 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/14 16:01:10 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	pipe_syntax(char input, char c)
{
	if (input != SPACE_CHARACTER && input != PIPE_CHARACTER)
			c++;
	if (input == '<')
			c = 0;
	if (input == PIPE_CHARACTER)
	{
		if (c == 0)
			return (-1);
		c = 0;
	}
	return (c);
}

int	check_pipe_syntax(char *input)
{
	int		c;
	char	*input_ptr;

	input_ptr = input;
	c = 0;
	while (*input)
	{
		c = pipe_syntax(*input, c);
		if (c == -1)
		{
			g_global.exit_status = 258;
			return (ft_error(1, PIPE_CHARACTER, NULL, input_ptr));
		}
		if (*input == '>')
		{
			input++;
			if (is_space(*input))
				c = 0;
		}
		input++;
	}
	if (!*input && c == 0)
	{
		g_global.exit_status = 1;
		return (ft_error(1, PIPE_CHARACTER, NULL, input_ptr));
	}
	return (1);
}

int	check_lg_syntax(char *input)
{
	char	**ptr;
	int		i;
	int		j;
	int		characters;
	char	*tmp;

	tmp = ft_strdup(input);
	ptr = ft_split_v2(tmp, '<', '>');
	i = -1;
	characters = 0;
	while (ptr[++i])
	{
		j = -1;
		while (ptr[i][++j])
		{
			if (ptr[i][j] != ' ' && ptr[i][j] != '<' && ptr[i][j] != '>')
				characters++;
		}
		if (characters == 0)
			return (ft_error(1, '<', NULL, input));
		characters = 0;
	}
	ft_free(ptr);
	free(tmp);
	return (0);
}

int	less_great_syntax(char *input, char *input_ptr, int *n, int *characters)
{
	if (*input != SPACE_CHARACTER && *input != '<' && *input != '>')
	{
		*n = 0;
		(*characters)++;
	}
	if (*input == '<')
	{
		(*n)++;
		if (input[1] == '>' && *n < 2)
			input[1] = GREAT_REDIRECTION;
		*characters = 0;
	}
	if (*input == '>')
	{
		(*n)++;
		if (input[1] == '<')
			return (ft_error(1, '<', NULL, input_ptr));
		*characters = 0;
	}
	if (*n > 2)
		return (ft_error(1, *input, NULL, input_ptr));
	return (1);
}

int	check_less_great_syntax(char *input)
{
	int		characters;
	char	*input_ptr;
	int		n;

	input_ptr = input;
	characters = 0;
	n = 0;
	if (skip_characters(&input, &characters) == -1)
		return (-1);
	while (*input)
	{
		if (less_great_syntax(input, input_ptr, &n, &characters) == -1)
			return (-1);
		input++;
	}
	if (!*input && characters == 0)
		return (ft_error(2, 0, "newline", input_ptr));
	return (1);
}
