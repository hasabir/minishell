/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:26:11 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/14 19:28:06 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../execution/execution.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

enum e_characters{
	SPACE_CHARACTER = ' ',
	PIPE_CHARACTER = '|',
	NULL_CHARACTER = '\0',
	PIPE_FLAG = -10,
	LESS_REDIRECTION,
	SPACE_FLAG,
	GREAT_REDIRECTION,
	OPTION_CHARACTER,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	EXPAND_CHARACTER,
	FILE_NAME
};

typedef struct s_data
{
	char	*cmd;
	char	**options;
	char	**arguments;
	int		output_file;
	int		input_file;
}t_data;

struct s_list
{
	t_data			*data;
	struct s_list	*next;
};

typedef struct s_list	t_list;

/*---------------Minishell_lexique------------------*/

char	*define_characters(char *input);
char	*lexical_analysis(char *input);

void	*define_double_quote(char	*ptr);
void	*define_single_quote(char	*ptr);
int		skip_characters(char **input, int *characters);

int		check_pipe_syntax(char *input);
int		check_less_great_syntax(char *input);
int		check_lg_syntax(char *input);

/*---------------Minishell_parsing------------------*/

int		open_out_file(t_list *list_command,
			char *matrix_input, int out_type, char **env);
int		open_in_file(t_list *list_command,
			char *matrix_input, int in_type, char **env);

char	*open_heredoc_files(char *matrix_input, int i, char **env);
char	**open_heredoc_matrix(char *input, char ***matrix_input, char **env);
void	exit_case(char *heredoc_file_name, char *delimiter);

int		unlink_heredoc_file(char *input_ptr, char *heredoc_file_name, int flag);
void	get_heredoc_name(char **heredoc_file_name, int c);
char	**free_heredoc(char **heredoc_matrix);

int		parsing(char *input, t_list **list_command, char **env);

int		take_in_out_files(t_list *list_command, char *matrix_input, char **env);

char	*expand(char *arg, char **env);
char	*ft_single_quote(char *cmd);
char	*ft_double_quote(char *cmd, char **env, int n);

void	skip_redirection(char **matrix_command_line, int **j);
int		get_length_options(char **matrix_command_line, int j);
int		get_length_arguments(char **matrix_command_line, int j);
char	*get_file_name(char *str);

void	set_arg(char ***arg, char **env);
void	take_options(t_list *list_command, char **matrix_command_line, int *j);
void	take_cmd(t_list *list_command, char **matrix_command_line, int *j);
void	take_argument(t_list *list_command, char **matrix_command_line, int *j);
void	expand_file(char **file_name, char **env, int n);

int		open_file(t_list *list_command, char *in_file_name);

/*---------------Minishell_utils------------------*/

char	**ft_split_v2(char *str, char c, char c2);

char	*ft_strstr(const char *s1, const char *s2);
void	ft_get_str(char **matrix_command_line);
void	ft_list_last(t_list **lst, t_list *new);
char	*search_env(char **env, char *to_find, char **arg);
char	*define_single_double_quote(char *arg);

int		search(char *str, char c);
char	*get_str(char *str, int j);
int		search_str(const char *s1, const char *s2);
int		search_characters(char *arg);
int		is_only_spaces(char *input);

t_list	*creat_list_of_command(void);
char	*set_redirection_to_origin(char *arg);
char	*set_origin(char *arg);
int		which_type_quote(char *cmd);
int		is_space(char c);

int		ft_error(int n, char option, char *str_option, char *input);
int		ft_free(char **str);
int		ft_perror(char *str, int flag);
char	*error(char *str);
char	**malloc_error(char **matrix);

void	handle_signals(int sig);
char	*new_arg(char *stock, char *arg, int flag);

void	print_list_command(t_list *list_command);
void	rl_replace_line(const char *text, int clear_undo);

#endif