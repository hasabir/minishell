/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:59:46 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/28 13:10:50 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	*define_expand(char *ptr)
{
	if (!ft_isalnum(ptr[1]) && ptr[1] != '_')
			*ptr = EXPAND_CHARACTER;
	return (ptr);
}

void	*define_double_quote(char	*ptr)
{
	ptr++;
	while (*ptr != '"' && *ptr)
	{
		if (*ptr == SPACE_CHARACTER)
				*ptr = SPACE_FLAG;
		else if (*ptr == PIPE_CHARACTER)
			*ptr = PIPE_FLAG;
		else if (*ptr == '<')
			*ptr = LESS_REDIRECTION;
		else if (*ptr == '>')
			*ptr = GREAT_REDIRECTION;
		else if (*ptr == '-')
			*ptr = OPTION_CHARACTER;
		else if (*ptr == '\'')
			*ptr = SINGLE_QUOTE;
		else if (*ptr == '$')
			define_expand(ptr);
		ptr++;
	}
	return(ptr);
}

void	*define_single_quote(char	*ptr)
{
	ptr++;
	while (*ptr != '\'' && *ptr)
	{
		if (*ptr == SPACE_CHARACTER)
				*ptr = SPACE_FLAG;
		else if (*ptr == PIPE_CHARACTER)
			*ptr = PIPE_FLAG;
		else if (*ptr == '<')
			*ptr = LESS_REDIRECTION;
		else if (*ptr == '>')
			*ptr = GREAT_REDIRECTION;
		else if (*ptr == '-')
			*ptr = OPTION_CHARACTER;
		else if (*ptr == '"')
			*ptr = DOUBLE_QUOTE;	
		else if (*ptr == '$')
			*ptr = EXPAND_CHARACTER;	
		ptr++;
	}
	return(ptr);
}

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
	while (*input && (is_space(*input) || *input == ' '))
		input++;
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

int	is_space(char c)
{
	if (c == '\t'|| c == '\f' || c == '\v' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

