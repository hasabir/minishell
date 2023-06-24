/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:39:08 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/14 23:02:20 by namine           ###   ########.fr       */
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
	if (!ft_isalnum(ptr[1]) && ptr[1] != '_' && c == 'd'
		&& ptr[1] != '?')
		*ptr = EXPAND_CHARACTER;
	return (ptr);
}

void	*define_double_quote(char *ptr)
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
	return (ptr);
}

void	*define_single_quote(char *ptr)
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
	return (ptr);
}

int	skip_characters(char **input, int *characters)
{
	while (**input && (is_space(**input) || **input == ' '))
		(*input)++;
	if (check_lg_syntax(*input) == -1)
		return (-1);
	while (**input && **input != SPACE_CHARACTER
		&& **input != '<' && **input != '>')
	{
		(*characters)++;
		(*input)++;
	}
	return (1);
}

int	is_only_spaces(char *input)
{
	int	i;

	if (!*input)
		return (0);
	i = -1;
	while (input[++i])
	{
		if (!is_space(input[i]))
			return (1);
	}
	return (0);
}
