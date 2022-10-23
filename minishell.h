/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:26:09 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/23 13:40:28 by hasabir          ###   ########.fr       */
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

typedef struct s_data
{
	char	*cmd;
	char	**options;
	char	*arguments;
	int		output_file;
	int		input_file;
	// t_output	*output_file;
	// t_input		*input_file;
}t_data;

typedef struct s_list
{
	t_data	*data;
	struct s_list *next;
}t_list;

char	*lexical_analysis(char *input);
int		search(char *str, char c);
int		ft_error(int n, char option, char *str_option);

t_list	*creat_list_of_command_2();
void	creat_list_of_command(t_list **command_line);
int		which_type_quote(char *cmd);
void	parsing(char *input, t_list **list_command, char **env);
// t_list	*parsing(char *input, t_list *list_command, char **env);
char	**ft_split_v2(char *str, char c, char c2);
void	ft_list_last(t_list **lst, t_list *new);

// void	set_arg(char **arg, char **env);
void	set_arg(char ***arg, char **env);
char	*search_env(char **env, char *to_find, char **arg);
void	ft_free(char **str);

char	*define_characters(char *input);

void	*define_double_quote(char	*ptr);
void	*define_single_quote(char	*ptr);
int		check_pipe_syntax(char *input);
int		check_lg_syntax(char *input);
int		check_less_great_syntax(char *input);
int		is_space(char c);

void	take_options(t_list *list_command, char **matrix_command_line, int *j);
void	take_cmd(t_list *list_command, char **matrix_command_line, int *j);
void	take_argument(t_list *list_command, char **matrix_command_line, int *j);
int		take_out_in_files(t_list *list_command, char **matrix_command_line);
void	*take_out_files(t_list *list_command, char **matrix_command_line, int *j);


int	search_index(const char *s1, const char *s2, size_t len);
char	*set_redirection_to_origin(char *arg);

char	*set_origin(char *arg);
int		search_characters(char *arg);
char	*expand(char *arg, char **env);
char	*ft_single_quote(char *cmd);
char	*ft_double_quote(char *cmd, char **env);


char	**split_redirection(char **matrix_command_line, int **j, char c);
char	*open_out_files(t_list *list_command ,char *matrix_line, char *stock, int index);
char	*get_file_name(char	*str, char c);
#endif
