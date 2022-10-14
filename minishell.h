/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:26:09 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/14 17:58:30 by hasabir          ###   ########.fr       */
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
	PIPE_FLAG = -8,
	SPACE_FLAG,
	LESS_REDIRECTION,
	GREAT_REDIRECTION,
	OPTION_CHARACTER,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	EXPAND_CHARACTER,
	DEFAULT_INPUT,
	DEFAULT_OUTPUT,
	GREAT,
	LESS,
	DOUBLE_GREAT,
	DOUBLE_LESS
};

typedef struct s_input_file
{
	char	*in_name;
	int		in_type;
}t_input;

typedef struct s_output_file
{
	char	*out_name;
	int		out_type;
}t_output;

typedef struct s_data
{
	char		*cmd;
	char		**options;
	char		*arguments;
	t_output	*output_file;
	t_input		*input_file;
}t_data;

typedef struct s_list
{
	t_data	*data;
	struct s_list *next;
}t_list;

char	*lexical_analysis(char *input);
int		search(char *str, char c);
int		ft_error(int n, char option, char *str_option);
void	creat_list_of_command(t_list **command_line);
int		which_type_quote(char *cmd);
t_list	*parsing(char *input, t_list *list_command, char **env);
char	**ft_split_v2(char *str, char c, char c2);
t_list	*ft_list_last(t_list *lst);
void	set_arg(char ***arg, char **env);
char	*search_env(char **env, char *to_find, char **arg);
void	ft_free(char **str);
char	*define_characters(char *input);
int		check_pipe_syntax(char *input);
int		check_lg_syntax(char *input);
int		check_less_great_syntax(char *input);

void	take_options(t_list *list_command, char **matrix_command_line, int *j);
void	take_cmd(t_list *list_command, char **matrix_command_line, int *j);
void	take_argument(t_list *list_command, char **matrix_command_line, int *j);
void	take_out_in_files(t_list *list_command, char **matrix_command_line);
void	take_out_files(t_list *list_command, char *matrix_command_line);


char	*set_origin(char *arg);
int		search_characters(char *arg);
char	*expand(char *arg, char **env);
char	*ft_single_quote(char *cmd);
char	*ft_double_quote(char *cmd, char **env);
#endif
