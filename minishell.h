/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:26:09 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/27 22:36:37 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "libft/libft.h"
#include "parsing/parsing.h"

typedef struct s_data
{
	char	*cmd;
	char	**options;
	char	*arguments;
	int		output_file;
	int		input_file;
	char	*out_file_name;
	char	*in_file_name;
}t_data;

typedef struct s_list
{
	t_data	*data;
	struct s_list *next;
}t_list;

#endif
