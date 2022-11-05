/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:59:46 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/05 15:59:17 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	*define_expand(char *ptr, char c)
{
	if (*ptr == '$' && c == 'n')
	{
		*ptr = EXPAND_CHARACTER;
		ptr++;
		*ptr = EXPAND_CHARACTER;
	}
	if (!ft_isalnum(ptr[1]) && ptr[1] != '_' && c == 'd')
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
			define_expand(ptr, 'd');
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
	char *input_ptr;

	input_ptr = input;
	c = 0;
	while (*input)
	{
		if (*input != SPACE_CHARACTER && *input != PIPE_CHARACTER)
			c++;
		if (*input == '<')
			c = 0;
		if (*input == '>')
		{
			input++;
			if (is_space(*input))
				c = 0;
		}
		if (*input == PIPE_CHARACTER)
		{
			if (c == 0)
				return (ft_error(1, PIPE_CHARACTER, NULL, input_ptr));
			c = 0;
		}
		input++;
	}
	if (!*input && c == 0)
		return(ft_error(1, PIPE_CHARACTER,  NULL, input_ptr));
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
			return(ft_error(1, '<', NULL, input));
		characters = 0;
	}
	ft_free(matrix_input);
	free(tmp);
	return (0);
}

int	check_less_great_syntax(char *input)
{
	int		characters;
	char	*input_ptr;
	int		n;

	input_ptr = input;
	characters = 0;
	n = 0;
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
		// printf("input = %s\n", input);
		if (*input != SPACE_CHARACTER && *input != '<' && *input != '>')
		{
			n = 0;
			characters++;
		}
		if (*input == '<')
		{
			n++;
			if (input[1] == '>')
				return (-1);
		}
		if (*input == '>')
		{
			n++;
			if (input[1] == '<')
				return (ft_error(1, '<', NULL, input_ptr));
			characters = 0;
		}
		// if (*input == '>')
		// {
		// 	n++;
		// 	if (input[1] == '|')
		// 		input[1] = PIPE_FLAG;
		// }
		if (n > 2)
			return(ft_error(1, '>', NULL, input_ptr)); // a gerer
		input++;
	}
	if (!*input && characters == 0)
		return (ft_error(2, 0, "newline", input_ptr));
	return (1);
}
