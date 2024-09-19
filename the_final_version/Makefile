# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 10:22:54 by tparratt          #+#    #+#              #
#    Updated: 2024/07/19 15:11:51 by mspasic          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRC			=	minishell.c \
					validation.c \
					first_split.c \
					second_split.c \
					trim.c \
					parsing.c \
					expansion.c \
					expansion2.c \
					expansion3.c \
					paths.c \
					env.c \
					utils.c \
					utils2.c \
					utils3.c \
					utils4.c \
					execution.c \
					execution2.c \
					error.c \
					redirect.c \
					retrim.c \
					children.c \
					fd_handling.c \
					dup2ing_fds.c \
					opening_files.c \
					signals.c \
					syntax_errors.c \
					heredoc.c \
					heredoc2.c \
					set_termios.c \
					builtins/echo-pwd-env.c \
					builtins/cd.c \
					builtins/export.c \
					builtins/export_unset_error.c \
					builtins/unset.c \
					builtins/builtin_check.c \
					builtins/exit.c \

LIBFT		=	libft/libft.a

OBJ			=	$(SRC:.c=.o)

CC			=	cc

RM			=	rm -f

CFLAGS		= -Wextra -Wall -Werror

$(NAME):	$(OBJ)
			make -C ./libft
			$(CC) $(CFLAGS) -g -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS) -lreadline

all:		$(NAME)

clean:
			make clean -C libft
			${RM} $(OBJ)

fclean: 	clean
			make fclean -C libft
			${RM} $(NAME) ${OBJ}

re:			fclean all

.PHONY:		all clean fclean re
