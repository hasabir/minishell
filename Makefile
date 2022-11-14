# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 18:29:03 by hasabir           #+#    #+#              #
#    Updated: 2022/11/14 15:51:38 by hasabir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a
NAME = minishell
UTILS = parsing/minishell_utils
PARSING = parsing/minishell_parsing
LEXIQUE = parsing/minishell_lexique
EXECUTION = execution
# CONTROL = @ssty -echoctl
SRCS = 	main.c ${LIBFT} ${UTILS}/utils.c ${LEXIQUE}/minishell_lexique.c \
		${UTILS}/minishell_split.c ${PARSING}/minishell_parsing.c \
		${PARSING}/parsing_utils.c ${LEXIQUE}/lexique_utils.c \
		${PARSING}/parsing_utils_2.c ${PARSING}/heredoc.c \
		${UTILS}/utils_2.c ${PARSING}/parsing_redirec.c \
		${PARSING}/redirection_utils.c ${PARSING}/parsing_utils_3.c \
		${EXECUTION}/ft_echo.c ${EXECUTION}/execution.c \
		${EXECUTION}/ft_env.c ${EXECUTION}/ft_unset.c ${EXECUTION}/ft_export.c \
		${UTILS}/utils_3.c ${LEXIQUE}/lexique_utils_2.c ${EXECUTION}/ft_exit.c \
		${UTILS}/utils_4.c ${EXECUTION}/utils_1.c ${EXECUTION}/ft_pwd.c \
		${EXECUTION}/ft_cd.c ${PARSING}/redirection_utils_2.c \
		${PARSING}/heredoc_utils.c ${EXECUTION}/utils_2.c ${EXECUTION}/export_utils.c \
		${EXECUTION}/execution_utils.c ${EXECUTION}/execution_utils_2.c \
		${UTILS}/utils_5.c

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

all : ${NAME}

${LIBFT} :
	@make -C libft

%.o: %.c
	@$(CC) ${CFLAGS} -c -o $@ $<
#-g3 -fsanitize=address
#  
${NAME} :${OBJS}
	@$(CC) $(OBJS) -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -o $(NAME)
	@echo "\033[92m|  Compilation Done  |\033[00m"

clean:
	@rm -rf ${OBJS}
	@rm -rf libft/*.o
	@echo "|  CLEANED |"

fclean: clean
	@rm -rf ${NAME}

re: fclean all
