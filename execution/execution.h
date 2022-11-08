/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:26:09 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/08 03:52:08 by namine           ###   ########.fr       */
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

typedef struct s_list	t_list;
void	execution(t_list *list_command, char **ptr_env, t_param *param);
void	ft_execve(char **ptr_env, t_list *list_command);
void	ft_export(t_list *list_command, t_param *param);
void    ft_unset(t_list *list_command, t_param *param);
void    ft_env(t_list *list_command, t_param *param);
char	*get_path(char **ptr_env, char *str);
char	**get_args(t_list	*list_command);
int		get_len(t_list	*list_command);
void	ft_echo(t_list *list_command);
void 	ft_exit(t_list *list_command);
#endif
