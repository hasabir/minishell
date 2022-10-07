/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:26:09 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/07 18:01:27 by hasabir          ###   ########.fr       */
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

#include <stdlib.h>

// #include "libft/libft.h"

enum characters{
	
	SPACE_CHARACTER = ' ',
	PIPE_CHARACTER = '|',
	NULL_CHARACTER = '\0',
	PIPE_FLAG = -2,
	SPACE_FLAG = -1,
	LESS_REDIRECTION = 1,
	GREAT_REDIRECTION,
	OPTION_CHARACTER,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	DEFAULT_INPUT = 10,
	DEFAULT_OUTPUT = 11
};

typedef struct s_data
{
	char	*cmd;
	char	**options;
	char	*arguments;
	char	input_file;
	char	output_file;
	// int		is_pipe;
}t_data;

typedef struct s_list
{
	t_data	*data;
	struct s_list *next;
}t_list;

char	*lexical_analysis(char *input);
int		search(char *str, char c);
char	**ft_split(char const *s, char c);
int		ft_error(int n, char option, char *str_option);
// t_list	*creat_list_of_command(t_list *command_line);
void	creat_list_of_command(t_list **command_line);
int		which_type_quote(char *cmd);
char	*ft_strjoin(char const *s1, char const *s2);

void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void	*s, size_t n);

t_list	*parsing(char *input, t_list *list_command);
// void	parsing(char *input);
char	*ft_strdup(char	*s1);

int		ft_strlen(char *str);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
char	**ft_split_v2(char *str, char c, char c2);

t_list	*ft_list_last(t_list *lst);

char	*ft_single_quote(char *cmd);
char	*ft_double_quote(char *cmd);
char	*set_command(char *cmd);

char	*define_characters(char *input);

int	check_pipe_syntax(char *input);
int	check_lg_syntax(char *input);
int	check_less_great_syntax(char *input);

#endif
