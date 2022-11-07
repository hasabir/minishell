/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:26:11 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/07 16:26:50 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "../execution/execution.h"
#include <unistd.h>

enum characters{
	
	SPACE_CHARACTER = ' ',
	PIPE_CHARACTER = '|',
	NULL_CHARACTER = '\0',
	PIPE_FLAG = -10,
	SPACE_FLAG,
	LESS_REDIRECTION,
	GREAT_REDIRECTION,
	OPTION_CHARACTER,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	EXPAND_CHARACTER,
	DOUBLE_GREAT,
	DOUBLE_LESS

};

typedef struct s_data
{
	char	*cmd;
	char	**options;
	char	**arguments;
	int		output_file;
	int		input_file;
	// char	*out_file_name;
	// char	*in_file_name;
	// int		heredoc;
}t_data;

typedef struct s_list
{
	t_data	*data;
	struct s_list *next;
}t_list;

typedef struct s_list t_list;

char	*lexical_analysis(char *input);
int		search(char *str, char c);
int		ft_error(int n, char option, char *str_option, char *input);

t_list	*creat_list_of_command_2();
void	creat_list_of_command(t_list **command_line);
int		which_type_quote(char *cmd);
int		parsing(char *input, t_list **list_command, char **env);
char	**ft_split_v2(char *str, char c, char c2);
void	ft_list_last(t_list **lst, t_list *(new));

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

void	skip_indirections(char **matrix_command_line, int **j);

void	take_options(t_list *list_command, char **matrix_command_line, int *j);
void	take_cmd(t_list *list_command, char **matrix_command_line, int *j);
void	take_argument(t_list *list_command, char **matrix_command_line, int *j);
int		take_out_in_files(t_list *list_command, char **matrix_command_line);

int		search_index(const char *s1, const char *s2, size_t len);
char	*set_redirection_to_origin(char *arg);
int		which_type_redirection(char *str);
void	ft_get_str(char **matrix_command_line);

char	*set_origin(char *arg);
int		search_characters(char *arg);
char	*expand(char *arg, char **env);
char	*ft_single_quote(char *cmd);
char	*ft_double_quote(char *cmd, char **env, int n);

int		split_out_redirection(char ***stock, char **matrix_command_line, int **j, int flag);
int		split_in_redirection(char ***stock, char **matrix_command_line, int **j, int flag);
char	*open_out_files(t_list *list_command ,char *matrix_line, char *stock, int index);
char	*open_in_files(t_list *list_command ,char *matrix_line, char *stock, int index);
char	*get_file_name(char	*str);

int		take_in_out_files(t_list *list_command, char *matrix_input, char **env);
int		open_out_file(t_list *list_command, char *matrix_input, int out_type, char **env);
int		open_in_file(t_list *list_command, char *matrix_input, int in_type, char **env);

int		get_length_options(char **matrix_command_line, int j);
int		get_length_arguments(char **matrix_command_line, int j);
char	*open_heredoc_files(char *matrix_input, int i,char **env);
void	expand_file(char **file_name, char **env, int n);
void	print_list_command(t_list *list_command);

char 	*get_str(char *str, int j);

char	*ft_strstr(const char *s1, const char *s2);
int		search_str(const char *s1, const char *s2);


int	skip_characters(char **input, int *characters);
# endif