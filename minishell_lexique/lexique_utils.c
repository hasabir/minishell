/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:59:46 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/14 19:34:41 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe_syntax(char *input)
{
	int	c;

	c = 0;
	while (*input)
	{
		if (*input != SPACE_CHARACTER && *input != PIPE_CHARACTER)
			c++;
		if (*input == PIPE_CHARACTER)
		{
			if (c == 0)
				return (ft_error(1, PIPE_CHARACTER, NULL));
			c = 0;
		}
		input++;
	}
	if (!*input && c == 0)
		return(ft_error(1, PIPE_CHARACTER,  NULL));
	return (1);
}

int	check_lg_syntax(char *input)
{
	char	**matrix_input;
	int		i;
	int		j;
	int		characters;
	char	*tmp;

	tmp = ft_strdup(input);
	matrix_input = ft_split_v2(tmp, '<', '>');
	i = -1;
	characters = 0;
	while (matrix_input[++i])
	{
		j = -1;
		while (matrix_input[i][++j])
		{
			if (matrix_input[i][j] != SPACE_CHARACTER && matrix_input[i][j] != '<'
					&& matrix_input[i][j] != '>')
				characters++;
		}
		if (characters == 0)
			return(ft_error(1, '<', NULL));
		characters = 0;
	}
	ft_free(matrix_input);
	return (0);
}

int	check_less_great_syntax(char *input)
{
	int characters;

	characters = 0;
	if (check_lg_syntax(input) == -1)
		return (-1);
	while (*input && *input != SPACE_CHARACTER && *input != '<' && *input != '>')
	{
		characters++;
		input++;
	}
	while (*input)
	{
		if (*input != SPACE_CHARACTER && *input != '<' && *input != '>')
			characters++;	
		if (*input != SPACE_CHARACTER && *input != '<' && *input != '>')
			characters++;	
		if (*input == '<')
		{
			if (input[1] == '>')
				return (-1);
		}
		if (*input == '>')
		{
			if (input[1] == '<')
				return (ft_error(1, '<', NULL));
			characters = 0;
		}
		input++;
	}
	if (!*input && characters == 0)
		return (ft_error(2, 0, "newline"));
	return (1);
}



