/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:31:44 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/11 13:40:36 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*define_characters_in_quote(char *input)
{
	int	i;

	i = 0;
	if (!input[i])
		return (NULL);
	return (input + i);
}

char	*define_special_characters(char *ptr)
{
	if (*ptr == '"')
	{
		ptr = define_double_quote(ptr);
		if (*ptr != '"')
			return (NULL);
	}
	else if (*ptr == '\'')
	{
		ptr = define_single_quote(ptr);
		if (*ptr != '\'')
			return (NULL);
	}
	else if (*ptr == '>' && ptr[1] && ptr[1] == '|')
		ptr[1] = PIPE_FLAG;
	else if (is_space(*ptr))
		*ptr = ' ';
	return (ptr);
}

char	*define_expand_characters(char *ptr)
{
	if (ptr[1] && ptr[1] == '$')
	{
		*ptr = EXPAND_CHARACTER;
		ptr++;
		*ptr = EXPAND_CHARACTER;
	}
	else if (!ptr[1] || (!ft_isalnum(ptr[1])
			&& ptr[1] != '?' && ptr[1] != '"' && ptr[1] != '\''
			&& ptr[1] != '_')
		|| is_space(ptr[1]))
		*ptr = EXPAND_CHARACTER;
	return (ptr);
}

char	*define_characters(char *input)
{
	char	*ptr;

	ptr = input;
	while (*ptr)
	{
		if (*ptr == '$')
			ptr = define_expand_characters(ptr);
		else
			ptr = define_special_characters(ptr);
		if (!ptr)
		{
			free(input);
			return (ptr);
		}
		ptr++;
	}
	return (input);
}

char	*lexical_analysis(char *input)
{
	input = define_characters(input);
	if (!input)
	{
		printf("Petit_shell: syntax error expected \"\n");
		return (NULL);
	}
	if (search(input, PIPE_CHARACTER) != 0)
	{
		if (check_pipe_syntax(input) == -1)
			return (NULL);
	}
	if (search(input, '<') != 0 || search(input, '>') != 0)
	{
		if (check_less_great_syntax(input) == -1)
			return (NULL);
	}
	return (input);
}
