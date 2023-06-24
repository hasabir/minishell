/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:26:09 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/15 03:54:30 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "../parsing/parsing.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>

typedef struct s_ev
{
	char			*env_var;
	char			*value;
	struct s_ev		*next;
}t_ev;

typedef struct s_param
{
	t_ev	*env;
	t_ev	*export;
}t_param;

typedef struct s_global
{
	int	exit_status;
	int	is_heredoc;
	int	pipe;
}t_global;

t_global				g_global;
typedef struct s_list	t_list;
int		ft_exit_status(t_list *list_command,
			char *msg, char *arg, int exit_code);
void	error_msg(t_list *list_command, char *cmd, char *msg, char *arg);
void	free_env_var_and_replace(t_ev *list, char *env_var, char *value);
void	execution(t_list *list_command, t_param *param);
void	ft_execve(char **ptr_env, t_list *list_command);
void	ft_export(t_list *list_command, t_param *param);
void	ft_unset(t_list *list_command, t_param *param);
void	ft_env(t_list *list_command, t_param *param);
void	ft_pwd(t_list *list_command);
void	ft_cd(t_list *list_command, t_param *param);
int		ft_strcmp(const char *s1, const char *s2);
char	*search_env_var(t_ev *list, char *str);
char	*get_path(char **ptr_env, char *str);
char	**get_args(t_list	*list_command);
int		check_argument_name(char *str);
int		get_len(t_list	*list_command);
void	ft_echo(t_list *list_command);
void	ft_exit(t_list *list_command, int print);
void	malloc_failed(void);
void	add_node(t_ev **list, char **ptr);
char	**ft_split_customized(char *str);
void	execute_cmd(t_list *list_command, t_param *param);
int		path_exists(char **ptr_env);
char	*get_path(char **ptr_env, char *cmd);
char	**get_args(t_list	*list_command);
int		get_len(t_list	*list_command);
int		is_builtins(char *cmd);
int		is_absolute_path(char *str);
void	ft_dup(t_list *list_command, int fd[2], int save);
char	**convert_to_arr(t_param *param);
void	ft_wait(int pid);
void	execute_child(t_list *list_command, t_param *param,
			int fd[2], int save);
void	execute_builtins(t_list *list_command, t_param *param, int print);
void	absolute_path(t_list *list_command, char **ptr_env);
void	execute_cmd(t_list *list_command, t_param *param);
void	relative_path(t_list *list_command, char **ptr_env);
void	initialize_env(t_param *param, char **env, int i);
void	initialize_export(t_param *param, char **env, int i);
char	**convert_to_arr(t_param *param);
int		fork_failed(char *arg, char *msg, int exit_code);

#endif
