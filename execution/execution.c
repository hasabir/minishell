/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:49:46 by namine            #+#    #+#             */
/*   Updated: 2022/11/13 13:24:10 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

int path_exists(char **ptr_env)
{
	int	i;
	
	i = 0;
	while (ptr_env[i])
	{
		if (!ft_strncmp("PATH", ptr_env[i], 4))
			return (i);
		i++;
	}
	return (-1);
}

char	*get_path(char **ptr_env, char *cmd)
{
	char **paths;
	char *s;
	int i;
	
	i = path_exists(ptr_env);
	if (i == -1)
		return (NULL);
	s = ft_strdup(ptr_env[i]);
	while (*s && *s != '=')
		s++;
	s++;
	paths = ft_split(s, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (!access(paths[i], X_OK | F_OK)) // x_ok ? and f_ok
			return (paths[i]);
		i++;
	}
	return (NULL);
}

char	**get_args(t_list	*list_command)
{
	char	**argv;
	int		i;
	int		j;

	argv = malloc(sizeof(char *) * (get_len(list_command) + 1));
	if (!argv)
		return (NULL);
	i = -1;
	if(list_command->data->cmd)
		argv[++i] = ft_strdup(list_command->data->cmd);
	i++;
	j = -1;
	if (list_command->data->options)
	{
		while (list_command->data->options[++j])
			argv[i++] = ft_strdup(list_command->data->options[j]);
	}
	j = -1;
	if (list_command->data->arguments)
	{
		while (list_command->data->arguments[++j])
			argv[i++] = ft_strdup(list_command->data->arguments[j]);		
	}
	argv[i] = NULL;
	return (argv);
}

int		get_len(t_list	*list_command)
{
	int count_args;
	int i;
	
	count_args = 0;
	if(list_command->data->cmd)
		count_args++;
	i = 0;
	if (list_command->data->options)
	{
		while (list_command->data->options[i])
		{
			count_args++;
			i++;
		}
	}
	i = 0;
	if (list_command->data->arguments)
	{
		if (list_command->data->arguments[i])
		{
			count_args++;
			i++;
		}
	}
	return (count_args);
}

int	is_builtins(char *cmd)
{
	return (
	!ft_strcmp(cmd, "echo") ||
	!ft_strcmp(cmd, "cd") ||
	!ft_strcmp(cmd, "pwd") ||
	!ft_strcmp(cmd, "export") ||
	!ft_strcmp(cmd, "unset") ||
	!ft_strcmp(cmd, "env") ||
	!ft_strcmp(cmd, "exit"));
}

void execute_builtins(t_list *list_command, t_param *param)
{
	if (!ft_strcmp(list_command->data->cmd, "echo"))
		ft_echo(list_command);
	if (!ft_strcmp(list_command->data->cmd, "cd"))
		ft_cd(list_command, param);
	if (!ft_strcmp(list_command->data->cmd, "pwd"))
		ft_pwd(list_command);
	if (!ft_strcmp(list_command->data->cmd, "export"))
		ft_export(list_command, param);
	if(!ft_strcmp(list_command->data->cmd, "unset"))
		ft_unset(list_command, param);
	if (!ft_strcmp(list_command->data->cmd, "env"))
		ft_env(list_command, param);
	if (!ft_strcmp(list_command->data->cmd, "exit"))
		ft_exit(list_command);
}

void ft_dup(t_list *list_command, int fd[2], int save)
{
	if (list_command->next)
	{
		dup2(fd[1], 1);
		close (fd[1]);
	}
	if (save != -1)
	{	
		dup2(save, 0);
		close (save);
	}
	if(list_command->data->output_file != 1)
		dup2(list_command->data->output_file, 1);
	if(list_command->data->input_file != 0)
	{
		dup2(list_command->data->input_file, 0);
		close(list_command->data->input_file);
	}
}

int is_absolute_path(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void execute_cmd(char **ptr_env, t_list *list_command, t_param *param)
{
	char	*path = NULL;
	// int 	a;
	
	if (is_builtins(list_command->data->cmd) == 1)
		execute_builtins(list_command, param);
	else if (list_command->data->cmd)
	{	
		if (!is_absolute_path(list_command->data->cmd))
		{
			if (path_exists(ptr_env) == -1)
				error_msg(list_command, list_command->data->cmd, "No such file or directory", 0);
			else
			{
				path = get_path(ptr_env, list_command->data->cmd);
				if (execve(path, get_args(list_command), ptr_env) == -1)
				{
					error_msg(list_command, list_command->data->cmd, "command not found", 0);
					global.exit_status = 127;
				}
			}
		}
		else
		{
			int i = chdir(list_command->data->cmd);
			int a = access(list_command->data->cmd, F_OK);
			int b = access(list_command->data->cmd, X_OK);
			if (a == -1) // success
			{
				printf("non trouvable\n");
			}
			else if (b == -1) // success
			{
				printf("non executable\n");
			}
			else if (i == 0)
			{
				printf("a directory\n");
			}
			else{
			path = ft_strdup(list_command->data->cmd);
			if (path != NULL)
			{
				if (execve(path, get_args(list_command), ptr_env) == -1)
					error_msg(list_command, list_command->data->cmd, strerror(errno), 0);
				printf("\n");
			}
				}
			}
	}
}

void multiple_pipes(char **ptr_env, t_list *list_command, t_param *param, int save)
{
	int		fd[2];
	int		pid;
	int		status;
	
	while (list_command)
	{
		if (pipe(fd) == -1)
			return ; // use perror or strerror 
		pid = fork();
		if (pid < 0)
			return ;
		signal(SIGINT, SIG_IGN);
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			// close(fd[0]);
			ft_dup(list_command, fd, save);
			execute_cmd(ptr_env, list_command, param);
			exit(global.exit_status);
		}
		if (save != -1)
			close (save);
		save = fd[0];
		close (fd[1]);
		list_command = list_command->next;
	}
	close (fd[0]);
	while(waitpid(pid, &status, 0) != -1);
	if (WIFEXITED(status))
		global.exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status)) //exit with signal
	{
		global.exit_status = 128 + WTERMSIG(status);
		if (global.exit_status == 131)
		{
			ft_putstr_fd("Quit: ", 1);
			ft_putnbr_fd(global.exit_status - 128, 1);
		}
		write (1, "\n", 1);
	}
	while(waitpid(-1, NULL, 0) != -1);
	signal(SIGINT, handle_signals);
}

void execution(t_list *list_command, char **ptr_env, t_param *param)
{
	int		save;
	
	save = -1;
	if (ft_lstsize((t_linked_list *)list_command) == 1 && is_builtins(list_command->data->cmd))
		execute_builtins(list_command, param);
	else
		multiple_pipes(ptr_env, list_command, param, save); // name !!! 
}
// wait for the last pipe
// get exit code
