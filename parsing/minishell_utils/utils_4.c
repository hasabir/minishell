/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:43 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/08 17:00:01 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*set_double_to_origin(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '\'')
		{
			while (arg[++i] != '\'')
				i++;
		}
		else if (arg[i] == PIPE_FLAG)
			arg[i] = PIPE_CHARACTER;
		else if (arg[i] == SPACE_FLAG)
			arg[i] = SPACE_CHARACTER;
		else if (arg[i] == OPTION_CHARACTER)
			arg[i] = '-';
		else if (arg[i] == SINGLE_QUOTE)
			arg[i] = '\'';
		else if (arg[i] == DOUBLE_QUOTE)
			arg[i] = '"';
		else if (arg[i] == EXPAND_CHARACTER)
			arg[i] = '$';
	}
	return(arg);
}