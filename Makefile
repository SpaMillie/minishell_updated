# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 10:22:54 by tparratt          #+#    #+#              #
#    Updated: 2024/06/17 15:53:47 by tparratt         ###   ########.fr        #
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
					paths.c \
					env.c \
					utils.c \
					utils2.c \
					execution.c \
					error.c \
					redirect.c \
					signals.c \
					heredoc.c \
					builtins/echo-pwd-env.c \
					builtins/cd.c \
					builtins/export.c \
					builtins/unset.c \
					builtins/builtin_check.c \
					builtins/exit.c \

LIBFT		=	libft/libft.a

OBJ			=	$(SRC:.c=.o)

CC			=	cc

RM			=	rm -f

CFLAGS		=	-I /Users/$(USER)/.brew/opt/readline/include/readline.h -Wextra -Wall -Werror -g -fsanitize=address

LDFLAGS 	=	-L /Users/$(USER)/.brew/opt/readline/lib

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