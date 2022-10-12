/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:26:09 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/12 12:47:35 by hasabir          ###   ########.fr       */
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

#include "libft/libft.h"

enum characters{
	
	SPACE_CHARACTER = ' ',
	PIPE_CHARACTER = '|',
	NULL_CHARACTER = '\0',
	PIPE_FLAG = -7,
	SPACE_FLAG,
	LESS_REDIRECTION,
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
int		ft_error(int n, char option, char *str_option);
// t_list	*creat_list_of_command(t_list *command_line);
void	creat_list_of_command(t_list **command_line);
int		which_type_quote(char *cmd);


t_list	*parsing(char *input, t_list *list_command, char **env);
// void	parsing(char *input);

char	**ft_split_v2(char *str, char c, char c2);

t_list	*ft_list_last(t_list *lst);

// char	*set_arg(char *cmd);
// char	**set_arg(char **arg);
void	set_arg(char ***arg, char **env);
char	*search_env(char **env, char *to_find, char *arg);

void	ft_free(char **str);

char	*define_characters(char *input);

int		check_pipe_syntax(char *input);
int		check_lg_syntax(char *input);
int		check_less_great_syntax(char *input);

void	take_options(t_list **list_command, char **matrix_command_line, int *j);
void	take_cmd(t_list **list_command, char **matrix_command_line, int *j);
void	take_argument(t_list **list_command, char **matrix_command_line, int *j);
char	*set_origin(char *arg);
int		search_characters(char *arg);

char	*expand(char *arg, char **env);
char	*ft_single_quote(char *cmd);
char	*ft_double_quote(char *cmd, char **env);

#endif
