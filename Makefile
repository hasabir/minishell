# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 18:29:03 by hasabir           #+#    #+#              #
#    Updated: 2022/11/03 19:07:25 by hasabir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a
NAME = minishell
UTILS = parsing/minishell_utils
PARSING = parsing/minishell_parsing
LEXIQUE = parsing/minishell_lexique
SRCS = 	main.c ${LIBFT}\
		${UTILS}/utils.c ${LEXIQUE}/minishell_lexique.c \
		${UTILS}/minishell_split.c ${PARSING}/minishell_parsing.c\
		${PARSING}/parsing_utils.c ${LEXIQUE}/lexique_utils.c\
		${PARSING}/parsing_utils_2.c\
		${UTILS}/utils_2.c ${PARSING}/parsing_redirec.c\
		${PARSING}/redirection_utils.c ${PARSING}/parsing_utils_3.c\
		${PARSING}/heredoc.c ${UTILS}/utils_3.c

OBJS = ${SRCS:.c=.o}

CC = gcc 

CFLAGS = -Wall -Wextra -Werror -g

all : ${NAME}

${LIBFT} :
	@make -C libft

%.o: %.c
	@$(CC) ${CFLAGS} -c -o $@ $<

${NAME} :${OBJS}
	@$(CC) $(OBJS) -lreadline -o $(NAME)
	@echo "\033[92m|  Compilation Done  |\033[00m"

clean:
	@rm -rf ${OBJS}
	@rm -rf libft/*.o
	@echo "|  CLEANED |"

fclean: clean
	@rm -rf ${NAME}

re: fclean all


#${UTILS}/utils_3.c is new