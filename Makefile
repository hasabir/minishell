# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 18:29:03 by hasabir           #+#    #+#              #
#    Updated: 2022/10/07 18:03:34 by hasabir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a
NAME = minishell
UTILS = minishell_utils
PARSING = minishell_parsing
LEXIQUE = minishell_lexique

SRCS = 	main.c ${LIBFT}\
		${UTILS}/utils.c ${LEXIQUE}/minishell_lexique.c \
		${UTILS}/minishell_split.c ${PARSING}/minishell_parsing.c\
		${PARSING}/parsing_utils.c ${LEXIQUE}/lexique_utils.c\
		${UTILS}/ft_lstlast_bonus.c

OBJS = ${SRCS:.c=.o}

CC = gcc 

CFLAGS = -Wall -Wextra -Werror

all : ${NAME}

${LIBFT} :
	@make -C libft

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

${NAME} :${OBJS}
	@$(CC) $(OBJS) -I/usr/local/include -lreadline -o $(NAME)
	@echo "\033[92m|  Compilation Done  |\033[00m"

clean:
	@rm -rf ${OBJS}
	@rm -rf libft/*.o
	@echo "|  CLEANED |"

fclean: clean
	@rm -rf ${NAME}

re: fclean all
