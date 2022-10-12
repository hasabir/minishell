/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:31:44 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/10 18:36:41 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



char	*define_characters_in_quote(char *input)
{
	int i;

	i = 0;
	if (!input[i])
		return (NULL);
	return (input + i);
}

char	*define_characters(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			i++;
			while (input[i] != '"' && input[i])
			{
				if (input[i] == SPACE_CHARACTER)
						input[i] = SPACE_FLAG;
				else if (input[i] == PIPE_CHARACTER)
					input[i] = PIPE_FLAG;
				else if (input[i] == '<')
					input[i] = LESS_REDIRECTION;
				else if (input[i] == '>')
					input[i] = GREAT_REDIRECTION;
				else if (input[i] == '-')
					input[i] = OPTION_CHARACTER;
				else if (input[i] == '\'')
					input[i] = SINGLE_QUOTE;	
				i++;
			}
			if (input[i] != '"')
				return (NULL);
		}
		else if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'' && input[i])
			{
				if (input[i] == SPACE_CHARACTER)
						input[i] = SPACE_FLAG;
				else if (input[i] == PIPE_CHARACTER)
					input[i] = PIPE_FLAG;
				else if (input[i] == '<')
					input[i] = LESS_REDIRECTION;
				else if (input[i] == '>')
					input[i] = GREAT_REDIRECTION;
				else if (input[i] == '-')
					input[i] = OPTION_CHARACTER;
				else if (input[i] == '"')
					input[i] = DOUBLE_QUOTE;	
				i++;
			}
			if (input[i] != '\'')
				return (NULL);
		}
		i++;
	}
	return (input);
}

char	*lexical_analysis(char *input)
{
	input = define_characters(input);
	if (!input)
	{
		printf(">\n");
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